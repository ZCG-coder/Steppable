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

#include "stpInterp/stpBetterTS.hpp"
#include "stpInterp/stpErrors.hpp"
#include "stpInterp/stpExprHandler.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpStore.hpp"

#include <iterator>

#if defined(_MSC_VER)
    #include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

using namespace std::literals;

namespace steppable::parser
{
    STP_Value STP_processFnCall(const TSNode* exprNode, const STP_InterpState& state)
    {
        TSNode nameNode = ts_node_child_by_field_name(*exprNode, "fn_name"s);

        std::string funcNameOrig = state->getChunk(&nameNode);
        std::string funcName = "STP_" + funcNameOrig;

        auto stpLib = state->getLoadedLib(0);
        auto funcPtr = stpLib->getSymbol(funcName);

        auto functionsVec = state->getCurrentScope()->functions;

        if (funcPtr == nullptr)
        {
            if (functionsVec.contains(funcNameOrig))
            {
                // call from Steppable-defined functions
                auto function = functionsVec[funcNameOrig];
                std::vector<STP_Argument> fnArgsVec = STP_extractArgVector(exprNode, state);

                std::vector<STP_Argument> posArgs;
                std::vector<STP_Argument> keywordArgs;

                STP_StringValMap declaredKeywordArgs = function.keywordArgs;
                STP_StringValMap givenKeywordArgs;

                std::ranges::copy_if(
                    fnArgsVec, std::back_inserter(posArgs), [](const STP_Argument& arg) { return arg.name.empty(); });
                std::ranges::copy_if(fnArgsVec, std::back_inserter(keywordArgs), [](const STP_Argument& arg) {
                    return not arg.name.empty();
                });

                std::ranges::transform(
                    keywordArgs, std::inserter(givenKeywordArgs, givenKeywordArgs.end()), [](const auto& pair) {
                        return std::make_pair(pair.name, STP_Value(pair.typeID, pair.value));
                    });

                if (posArgs.size() != function.posArgNames.size())
                {
                    std::vector<std::string> missingArgsNames;
                    std::copy(function.posArgNames.begin() + static_cast<ssize_t>(function.posArgNames.size()) -
                                  static_cast<ssize_t>(posArgs.size()),
                              function.posArgNames.end(),
                              missingArgsNames.begin());

                    STP_throwError(
                        *exprNode,
                        state,
                        format::format("Missing positional arguments. Expect {0}"s,
                                                    {
                                                        stringUtils::join(missingArgsNames, ","s),
                                                    }));
                    return STP_Value(STP_TypeID::NONE);
                }

                STP_StringValMap argMap;
                for (size_t i = 0; i < posArgs.size(); i++)
                {
                    std::string posArgName = function.posArgNames[i];
                    const STP_Argument& currentArg = posArgs[i];
                    argMap.insert_or_assign(posArgName, STP_Value(currentArg.typeID, currentArg.value));
                }
                argMap.merge(declaredKeywordArgs);
                argMap.merge(givenKeywordArgs);

                return function.interpFn(argMap);
            }
            STP_throwError(
                *exprNode, state, format::format("Function {0} is not defined."s, { funcNameOrig }));
            return STP_Value(STP_TypeID::NONE);
        }

        std::vector<STP_Argument> fnArgsVec = STP_extractArgVector(exprNode, state);

        auto args = STP_ArgContainer(fnArgsVec, {});
        auto* val = static_cast<STP_ValuePrimitive*>(funcPtr(&args));

        if (not val->error.empty())
            STP_throwError(*exprNode, state, val->error);

        return STP_Value(val->typeID, val->data);
    }
} // namespace steppable::parser
