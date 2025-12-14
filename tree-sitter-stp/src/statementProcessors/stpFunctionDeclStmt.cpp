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
#include "stpInterp/stpProcessor.hpp"

using namespace std::literals;

namespace steppable::parser
{
    void STP_processFuncDefinition(const TSNode* node, const STP_InterpState& state)
    {
        TSNode fnNameNode = ts_node_child_by_field_name(*node, "fn_name"s);
        std::string fnName = state->getChunk(&fnNameNode);

        const TSNode posArgsNode = ts_node_child_by_field_name(*node, "pos_args"s);
        const TSNode keywordArgsNode = ts_node_child_by_field_name(*node, "keyword_args"s);

        std::vector<std::string> posArgNames;
        STP_StringValMap keywordArgs;

        if (not ts_node_is_null(posArgsNode))
        {
            const uint32_t posArgsCount = ts_node_named_child_count(posArgsNode);

            for (uint32_t i = 0; i < posArgsCount; i++)
            {
                TSNode paramNode = ts_node_named_child(posArgsNode, i);
                std::string paramName = state->getChunk(&paramNode);
                posArgNames.emplace_back(paramName);
            }
        }
        if (not ts_node_is_null(keywordArgsNode))
        {
            const uint32_t keywordArgsCount = ts_node_named_child_count(posArgsNode);

            for (uint32_t i = 0; i < keywordArgsCount; i++)
            {
                TSNode paramNode = ts_node_named_child(keywordArgsNode, i);
                TSNode paramNameNode = ts_node_named_child(paramNode, 0);
                TSNode paramValueNode = ts_node_named_child(paramNode, 1);

                STP_Value defaultVal = STP_handleExpr(&paramValueNode, state);
                std::string paramName = state->getChunk(&paramNameNode);
                keywordArgs.insert_or_assign(paramName, defaultVal);
            }
        }

        TSNode bodyNode = ts_node_child_by_field_name(*node, "fn_body"s);
        if (STP_checkRecursiveNodeSanity(bodyNode, state))
            return;

        STP_FunctionDefinition fn;

        fn.interpFn = [&](const STP_StringValMap& map) -> STP_Value {
            auto* scope = state->addChildScope();

            scope->variables = map;
            // default return value
            scope->addVariable("04795", STP_Value(STP_TypeID::NONE));

            state->setCurrentScope(scope);

            STP_processChunkChild(*node, state, false);
            STP_Value ret = state->getCurrentScope()->getVariable(node, "04795");
            state->setCurrentScope(scope->parentScope);

            return ret;
        };
        fn.posArgNames = posArgNames;
        fn.keywordArgs = keywordArgs;

        state->getCurrentScope()->addFunction(fnName, fn);
    }
} // namespace steppable::parser
