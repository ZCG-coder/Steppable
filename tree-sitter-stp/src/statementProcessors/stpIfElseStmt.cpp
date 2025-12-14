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

#include "stpInterp/stpExprHandler.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpProcessor.hpp"
#include "tree_sitter/api.h"

using namespace std::literals;

namespace steppable::parser
{
    void STP_processIfElseStmt(const TSNode* node, const STP_InterpState& state)
    {
        // if_else_stmt := 'if'      expr '{' if_clause_stmt '}'
        //                 'else if' expr '{' statement '}'
        //                 'else'         '{' else_clause_stmt '}'
        TSNode exprNode = ts_node_named_child(*node, 0);
        STP_Value res = STP_handleExpr(&exprNode, state);
        TSNode ifClauseStmtNode = ts_node_next_named_sibling(exprNode);
        TSNode lastNode = ifClauseStmtNode;

        if (res.asBool(&exprNode))
        {
            STP_processChunkChild(ifClauseStmtNode, state, true);
            return;
        }

        if (ts_node_is_null(lastNode))
        {
            // Don't go further if there is no elseif and else statements
            return;
        }

        while (true)
        {
            TSNode elseifClauseNode = ts_node_next_named_sibling(lastNode);
            if (ts_node_is_null(elseifClauseNode))
                break;
            if (ts_node_type(elseifClauseNode) != "elseif_clause"s)
                break;
            lastNode = elseifClauseNode;

            TSNode elseifExprNode = ts_node_named_child(elseifClauseNode, 0);
            TSNode elseifClauseStmtNode = ts_node_named_child(elseifClauseNode, 1);
            res = STP_handleExpr(&elseifExprNode, state);

            if (res.asBool(&exprNode))
            {
                STP_processChunkChild(elseifClauseStmtNode, state, true);
                return;
            }
        }

        // Handle else statement
        if (ts_node_is_null(lastNode))
        {
            // If there is no else statement, skip it
            return;
        }

        const TSNode elseClauseNode = ts_node_next_named_sibling(lastNode);
        if (ts_node_is_null(elseClauseNode))
            return;
        TSNode elseClauseStmtNode = ts_node_named_child(elseClauseNode, 0);
        STP_processChunkChild(elseClauseStmtNode, state, true);
    }
} // namespace steppable::parser