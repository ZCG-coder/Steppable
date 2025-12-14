/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy                   *
 * of this software and associated documentation files (the "Software"), to deal                  *
 * in the Software without restriction, including without limitation the rights                   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                      *
 * copies of the Software, and to permit persons to whom the Software is                          *
 * furnished to do so, subject to the following conditions:                                       *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all                 *
 * copies or substantial portions of the Software.                                                *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                  *
 * SOFTWARE.                                                                                      *
 **************************************************************************************************/

#include "stpInterp/stpStore.hpp"

#include "steppable/mat2d.hpp"
#include "steppable/number.hpp"
#include "stpInterp/stpApplyOperator.hpp"
#include "stpInterp/stpErrors.hpp"
#include "util.hpp"

#include <any>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <utility>
#if defined(_WIN32)
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

using namespace std::literals;

/**
 * @namespace steppable::parser
 * @brief The parser for Steppable code.
 */
namespace steppable::parser
{
    STP_DynamicLibrary::STP_DynamicLibrary(const std::string& _path) : handle(nullptr)
    {
        std::string path = _path;
#if defined(WINDOWS)
        path += ".dll";
        handle = (void*)LoadLibraryA(path.c_str());
#elif defined(MACOSX)
        path = "lib" + path + ".dylib";
        handle = dlopen(path.c_str(), RTLD_LAZY);
#else
        path = "lib" + path + ".so";
        handle = dlopen(path.c_str(), RTLD_LAZY);
#endif
    }

    STP_DynamicLibrary::~STP_DynamicLibrary()
    {
#if defined(_WIN32)
        if (handle != nullptr)
            FreeLibrary((HMODULE)handle);
#else
        if (handle != nullptr)
            dlclose(handle);
#endif
    }

    STP_ExportFuncT STP_DynamicLibrary::getSymbol(const std::string& name)
    {
#if defined(_WIN32)
        if (handle != nullptr)
        {
            auto* ptr = reinterpret_cast<void* (*)(void*)>(GetProcAddress((HMODULE)handle, name.c_str()));
            return ptr;
        }
        return nullptr;
#else
        if (handle != nullptr)
        {
            auto* ptr = reinterpret_cast<STP_ExportFuncPtr*>( // NOLINT(*-pro-type-reinterpret-cast)
                dlsym(handle, name.c_str()));
            return ptr;
        }
        return nullptr;
#endif
    }

    bool STP_DynamicLibrary::isLoaded() const { return handle != nullptr; }

    STP_Value STP_Value::applyBinaryOperator(const TSNode* node,
                                             const std::string& _operatorStr,
                                             const STP_Value& rhs) const
    {
        std::string operatorStr = _operatorStr;
        operatorStr = stringUtils::bothEndsReplace(operatorStr, ' ');

        STP_TypeID lhsType = this->typeID;
        STP_TypeID rhsType = rhs.typeID;
        STP_Value returnVal(STP_TypeID::NONE);

        const std::unique_ptr<STP_TypeID> typeIdPtr =
            determineBinaryOperationFeasibility(node, lhsType, operatorStr, rhsType);
        if (typeIdPtr == nullptr)
            return returnVal;

        STP_TypeID retType = *typeIdPtr;

        std::any value = this->data;
        std::any rhsValue = rhs.data;

        returnVal.typeID = retType;
        returnVal.typeName = STP_typeNames.at(retType);

        std::any returnValueAny = performBinaryOperation(node, lhsType, value, operatorStr, rhsType, rhsValue);

        if (not returnValueAny.has_value())
            STP_throwError(*node, STP_getState(), "This operation is not supported at present"s);
        returnVal.data = returnValueAny;

        return returnVal;
    }

    STP_Value STP_Value::applyUnaryOperator(const TSNode* node, const std::string& _operatorStr) const
    {
        std::string operatorStr = _operatorStr;
        operatorStr = stringUtils::bothEndsReplace(operatorStr, ' ');

        const std::any returnValAny = performUnaryOperation(node, typeID, operatorStr, data);
        if (not returnValAny.has_value())
            return STP_Value(STP_TypeID::NONE);

        STP_Value returnValue(typeID, returnValAny);
        return returnValue;
    }

    bool STP_Value::asBool(const TSNode* node) const
    {
        switch (typeID)
        {
        case STP_TypeID::NONE:
            return false;
        case STP_TypeID::NUMBER:
        {
            const auto val = std::any_cast<Number>(data);
            return val != 0;
        }
        case STP_TypeID::MATRIX_2D:
        {
            const auto val = std::any_cast<Matrix>(data);
            return std::ranges::all_of(val.getData(), [](const std::vector<Number>& vec) {
                return std::ranges::all_of(vec, [](const Number& n) { return n != 0; });
            });
        }
        case STP_TypeID::STRING:
        {
            const auto val = std::any_cast<std::string>(data);
            return not val.empty();
        }
        default:
        {
            STP_throwError(*node,
                           STP_getState(),
                           format::format("Cannot convert {0} to a logical type"s,
                                          {
                                              STP_typeNames.at(typeID),
                                          }));
            return false;
        }
        }
    }

    void STP_Scope::addVariable(const std::string& name, const STP_Value& data)
    {
        auto* currentScope = this;
        while (currentScope != nullptr)
        {
            if (currentScope->variables.contains(name))
            {
                currentScope->variables.insert_or_assign(name, data);
                return;
            }
            currentScope = currentScope->parentScope;
        }

        variables.insert_or_assign(name, data);
    }

    STP_Value STP_Scope::getVariable(const TSNode* node, const std::string& name) const
    {
        if (!variables.contains(name))
        {
            if (parentScope == nullptr)
            {
                STP_throwError(*node, STP_getState(), format::format("Variable {0} is not defined"s, { name }));
                return STP_Value(STP_TypeID::NONE, nullptr);
            }
            return parentScope->getVariable(node, name);
        }
        return variables.at(name);
    }

    void STP_Scope::addFunction(const std::string& name, const STP_FunctionDefinition& fn) { functions[name] = fn; }

    STP_FunctionDefinition STP_Scope::getFunction(const TSNode* node, const std::string& name) const
    {
        if (functions.contains(name))
            return functions.at(name);

        if (parentScope == nullptr)
        {
            STP_throwError(*node, STP_getState(), format::format("Cannot find function {0} in scope"s, { name }));
            return {};
        }
        return parentScope->getFunction(node, name);
    }

    std::string STP_Scope::present() const
    {
        std::stringstream ss;

        if (variables.empty())
            ss << "(No variables are present.)" << "\n";

        for (const auto& [name, val] : variables)
            ss << val.present(name) << "\n";

        return ss.str();
    }

    STP_InterpStoreLocal::STP_InterpStoreLocal() :
        globalScope(std::make_unique<STP_Scope>()), currentScope(globalScope.get())
    {
        STP_DynamicLibrary stpFnLib("steppable");
        loadedLibraries.push_back(stpFnLib);
    }

    void STP_InterpStoreLocal::setChunk(const std::string& newChunk, const size_t& chunkStart, const size_t& chunkEnd)
    {
        chunk = newChunk;
        this->chunkStart = chunkStart;
        this->chunkEnd = chunkEnd;
    }

    std::string STP_InterpStoreLocal::getChunk(const TSNode* node)
    {
        if (node == nullptr)
            return chunk;

        uint32_t start = ts_node_start_byte(*node);
        uint32_t end = ts_node_end_byte(*node);
        std::string text;
        if (end - chunkStart <= chunk.size())
            text = chunk.substr(start - chunkStart, end - start);
        return text;
    }

    STP_Scope* STP_InterpStoreLocal::addChildScope(STP_Scope* parent)
    {
        STP_Scope* scope = allocateScope();
        if (!parent)
            scope->parentScope = currentScope;
        else
            scope->parentScope = parent;
        return scope;
    }

    void STP_InterpStoreLocal::setCurrentScope(STP_Scope* newScope)
    {
        currentScope = nullptr;
        if (newScope != nullptr)
            currentScope = newScope;
    }

    void STP_InterpStoreLocal::setFile(const std::string& newFile) { file = newFile; }

    std::string STP_InterpStoreLocal::getFile() const { return file; }

    STP_Scope* STP_InterpStoreLocal::allocateScope()
    {
        scopeArena.push_back(std::make_unique<STP_Scope>());
        return scopeArena.back().get();
    }
} // namespace steppable::parser
