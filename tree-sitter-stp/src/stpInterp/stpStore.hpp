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

#pragma once
#include "fn/calc.hpp"
#include "steppable/stpArgSpace.hpp"
#include "steppable/stpTypeName.hpp"

extern "C" {
#include <tree_sitter/api.h>
}

#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @namespace steppable::parser
 * @brief The parser for Steppable code.
 */
namespace steppable::parser
{
    /**
     * @class STP_DynamicLibrary
     * @brief A wrapper class around `dlsym` and `LoadLibraryA`.
     * @details A wrapper class that allocates and deallocates memory dynamically to load platform-specific shared
     * libraries.
     */
    class STP_DynamicLibrary // NOLINT(*-special-member-functions)
    {
    public:
        /**
         * @brief Initialize the wrapper class.
         *
         * @param path The path to the shared libraries.
         */
        explicit STP_DynamicLibrary(const std::string& path);

        /**
         * @brief Destroys the wrapper class.
         * @details Deallocates memory allocated to the shared library.
         */
        ~STP_DynamicLibrary();

        /**
         * @brief Get a Steppable function symbol from the shared library.
         * @details Get a Steppable function from the shared library that takes a `STP_ArgContainer` object and returns
         * a `STP_ValuePrimitive` object.
         *
         * @param name Name of the Steppable function.
         * @return A `std::function` function pointer to that function.
         */
        STP_ExportFuncT getSymbol(const std::string& name);

        /**
         * @brief Determine if the shared library is loaded.
         * @return True if the shared library is loaded. False otherwise.
         */
        [[nodiscard]] bool isLoaded() const;

    private:
        void* handle; ///< The handle of the loaded shared library.
    };

    /**
     * @struct STP_Value
     * @brief A more advanced version of `STP_ValuePrimitive` that allows operations to be done on.
     */
    class STP_Value : public STP_ValuePrimitive
    {
        bool isConstant = false;

    public:
        /**
         * @brief Apply a binary operator to the value.
         *
         * @param node The binary operation node.
         * @param _operatorStr The binary operator.
         * @param rhs The other value.
         *
         * @return The resulting value after the operation is done.
         */
        [[nodiscard]] STP_Value applyBinaryOperator(const TSNode* node,
                                                    const std::string& _operatorStr,
                                                    const STP_Value& rhs) const;

        /**
         * @brief Apply a unary operator to the value.
         *
         * @param node The unary operation node.
         * @param _operatorStr The unary operator.
         *
         * @return The resulting value after the operation is done.
         */
        [[nodiscard]] STP_Value applyUnaryOperator(const TSNode* node, const std::string& _operatorStr) const;

        /**
         * @brief Convert the value to a C++ boolean value.
         *
         * @param node The expression node.
         * @return A boolean value.
         */
        [[nodiscard]] bool asBool(const TSNode* node) const;

        /**
         * @brief Initialize a new `STP_Value` object.
         * @details `STP_Value` contains a `std::any` value and a corresponding `STP_TypeID` type identifier.
         *
         * @param type The type of the value stored.
         * @param data The data value of the object.
         * @param isConstant_ Whether the value is supposed to be constant.
         */
        explicit STP_Value(const STP_TypeID& type, const std::any& data = {}, const bool& isConstant_ = false) :
            STP_ValuePrimitive(type, data), isConstant(isConstant_)
        {
        }

        [[nodiscard]] bool getIsConstant() const { return isConstant; }
    };

    /**
     * @brief Alias for a map with keys of strings and values of `STP_Value`.
     */
    using STP_StringValMap = std::unordered_map<std::string, STP_Value>;

    /**
     * @struct STP_FunctionDefinition
     * @brief A function declaration statement expressed as a functor object.
     */
    struct STP_FunctionDefinition
    {
        TSNode fnNode; ///< Function declaration node. Store it here so that it does not get deallocated.

        TSTree* fnTree; ///< Tree attached to a function declaration node. Store it here so that it does not get
                        ///< deallocated.

        std::vector<std::string> posArgNames; ///< Positional argument names.

        STP_StringValMap keywordArgs; ///< Keyword arguments specified.

        std::function<STP_Value(STP_StringValMap)>
            interpFn; ///< A function that executes Steppable code when the functor is called.

        /**
         * @brief Call the functor with arguments.
         *
         * @param args Arguments to pass to the Steppable function.
         * @return Value returned from the function.
         */
        STP_Value operator()(const STP_StringValMap& args) const { return interpFn(args); }
    };

    /**
     * @struct STP_Scope
     * @brief A storage object for a local scope.
     * @details The scope object does not contain functionality to list children scopes. Except for the global scope, no
     * scopes are stored by the interpreter. Implementations need to store the pointer to the scopes created and set
     * the global scope as parent to create and access new scopes.
     */
    struct STP_Scope
    {
        STP_Scope(const STP_Scope&) = delete;
        STP_Scope& operator=(const STP_Scope&) = delete;
        STP_Scope(STP_Scope&&) = delete;
        STP_Scope& operator=(STP_Scope&&) = delete;
        STP_Scope() = default;
        ~STP_Scope() = default;

        STP_StringValMap variables; ///< Variables declared in the current scope.

        std::map<std::string, STP_FunctionDefinition> functions; ///< Functions in the current scope.

        STP_Scope* parentScope = nullptr; ///< Pointer to the parent scope. nullptr if global.

        // Child scopes are owned and managed here. This prevents leaks and dangling pointers.
        std::vector<std::unique_ptr<STP_Scope>> children;

        /**
         * @brief Add a variable to the current scope.
         *
         * @param name The name of the variable.
         * @param data The `STP_Value` value of the variable.
         */
        void addVariable(const std::string& name, const STP_Value& data);

        /**
         * @brief Get a variable from the scope.
         * @details Return the value corresponding to the name of the variable. If no such variable exists, recursively
         * visit parent scopes until reaching the global scope, until a value of the variable defined in parent scopes.
         * Else, throws an error and gives a Steppable None object.
         *
         * @param node The expression node that fetches the variable. Only collected for bug checking purposes.
         * @param name The name of the variable to get.
         *
         * @return The value of the variable.
         */
        STP_Value getVariable(const TSNode* node, const std::string& name) const;

        /**
         * @brief Add a function declaration to the current scope.
         *
         * @param name Name of the function.
         * @param fn `STP_FunctionDefinition` object containing a Steppable function node.
         */
        void addFunction(const std::string& name, const STP_FunctionDefinition& fn);

        /**
         * @brief Get a function from the scope.
         * @details Return the value corresponding to the name of the function. If no such function exists, recursively
         * visit parent scopes until reaching the global scope, until a value of the function defined in parent scopes.
         * Else, throws an error and gives a Steppable None object.
         *
         * @param node The expression node that calls the function. Only collected for bug checking purposes.
         * @param name The name of the function to get.
         *
         * @return The function object.
         */
        STP_FunctionDefinition getFunction(const TSNode* node, const std::string& name) const;

        /**
         * @brief Presents all variables in this storage object. Only used for debugging.
         * @return String containing all presented forms of variables in the object.
         */
        [[nodiscard]] std::string present() const;

        /**
         * @brief Add a child scope and return a pointer to it.
         * @param child The child scope to add (must be a unique_ptr).
         * @return Pointer to the added child scope.
         */
        STP_Scope* addChild(std::unique_ptr<STP_Scope> child)
        {
            child->parentScope = this;
            children.push_back(std::move(child));
            return children.back().get();
        }
    };

    /**
     * @class STP_InterpStoreLocal
     * @brief Storage object representing the interpreter state.
     */
    class STP_InterpStoreLocal
    {
        std::vector<std::unique_ptr<STP_Scope>> scopeArena; ///< Arena for all allocated scopes.

        std::unique_ptr<STP_Scope> globalScope; ///< The global scope of the program.
        STP_Scope* currentScope = nullptr; ///< The current scope the code is executing in. Non-owning pointer.

        std::string chunk; ///< The chunk that the interpreter is executing.
        size_t chunkStart = 0; ///< Not used.
        size_t chunkEnd = 0; ///< Not used.

        bool interactive = false; ///< Whether the interpreter is taking interactive commands.

        STP_ExecState execState = STP_ExecState::NORMAL; ///< Flags of execution state.

        std::string file; ///< File name to the current parsing file.

        std::vector<STP_DynamicLibrary> loadedLibraries; ///< Imported dynamic libraries.

    public:
        /**
         * @brief Initializes a new interpreter state.
         */
        STP_InterpStoreLocal();

        STP_Scope* allocateScope();

        /**
         * @brief Gets whether the interpreter is running in interactive mode.
         * @return True if running in interactive mode. False otherwise.
         */
        [[nodiscard]] bool isInteractive() const { return interactive; }

        /**
         * @brief Set the interpreter to operate in interactive mode.
         */
        void setInteractive() { interactive = true; }

        /**
         * @brief Set a new chunk for the interpreter.
         *
         * @param newChunk A new chunk of text for the interpreter.
         * @param chunkStart Not used.
         * @param chunkEnd Not used.
         */
        void setChunk(const std::string& newChunk, const size_t& chunkStart, const size_t& chunkEnd);

        /**
         * @brief Get the current parsing chunk of the interpreter.
         *
         * @param node If not `nullptr`, gets the chunk of text associated with the Tree-sitter node.
         * @return The current parsing chunk of the interpreter.
         */
        std::string getChunk(const TSNode* node = nullptr);

        /**
         * @brief Add a child scope to the program.
         *
         * @param parent Parent scope.
         * @return A new `STP_Scope` scope object.
         */
        [[nodiscard]] STP_Scope* addChildScope(STP_Scope* parent = nullptr);

        /**
         * @brief Set a new scope to execute code in.
         *
         * @param newScope New scope to execute code in.
         */
        void setCurrentScope(STP_Scope* newScope);

        /**
         * @brief Get the current scope that code is executing in.
         * @return The current scope that code is executing in.
         */
        STP_Scope* getCurrentScope() { return currentScope; }

        /**
         * @brief Get the global scope of a program.
         * @return The global scope of a program.
         */
        auto getGlobalScope() { return globalScope.get(); };

        /**
         * @brief Set a new parsing file name.
         *
         * @param newFile The new parsing file name.
         */
        void setFile(const std::string& newFile);

        /**
         * @brief Get the current execution state.
         * @return Current execution state flag.
         */
        [[nodiscard]] auto getExecState() const { return execState; }

        /**
         * @brief Set a execution state flag.
         *
         * @param state New execution state flag.
         */
        void setExecState(const STP_ExecState& state) { execState = state; }

        /**
         * @brief Get the file name of the current parsing file.
         * @return The file name of the current parsing file.
         */
        [[nodiscard]] std::string getFile() const;

        /**
         * @brief Get a loaded shared library.
         *
         * @param count Index of a shared library in the loaded shared library registry.
         * @return A `std::unique_ptr` to the loaded library.
         */
        std::unique_ptr<STP_DynamicLibrary> getLoadedLib(const size_t& count)
        {
            if (count > loadedLibraries.size())
                return nullptr;
            return std::make_unique<STP_DynamicLibrary>(loadedLibraries[count]);
        }
    };
} // namespace steppable::parser
