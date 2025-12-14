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

#include "stpInterp/stpErrors.hpp"
#include "stpInterp/stpExprHandler.hpp"
#include "stpInterp/stpInit.hpp"
#include "tree_sitter/api.h"

#include <iostream>

using namespace std::literals;

namespace steppable::parser
{
    void STP_handleAssignment(const TSNode* node, const STP_InterpState& state = nullptr)
    {
        // assignment := nameNode "=" exprNode
        const TSNode nameNode = ts_node_child(*node, 0);
        const TSNode exprNode = ts_node_child(*node, 2);

        std::string name = state->getChunk(&nameNode);
        name = stringUtils::bothEndsReplace(name, ' ');
        bool printValue = false;

        const TSNode semicolonSibling = ts_node_next_sibling(exprNode);
        if (ts_node_is_null(semicolonSibling))
            printValue = true; // NOLINT(*-branch-clone)
        else if (ts_node_type(semicolonSibling) != ";"s)
            printValue = true;

        STP_Scope* current_scope = state->getCurrentScope();
        if (current_scope->variables.contains(name))
        {
            const STP_Value existingVar = current_scope->getVariable(node, name);
            if (existingVar.getIsConstant())
            {
                STP_throwError(*node, STP_getState(), "Re-assigning constant variables.");
                return;
            }
        }
        // Write to scope / global variables
        const STP_Value val = STP_handleExpr(&exprNode, state, printValue, name);
        current_scope->addVariable(name, val);
    }
} // namespace steppable::parser
