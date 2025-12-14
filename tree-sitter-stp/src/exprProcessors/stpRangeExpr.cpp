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

#include "steppable/mat2d.hpp"
#include "stpInterp/stpBetterTS.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpStore.hpp"
#include "tree_sitter/api.h"

using namespace steppable::stringUtils;
using namespace std::literals;

namespace steppable::parser
{
    STP_Value STP_handleRangeExpr(const TSNode* exprNode, const STP_InterpState& state)
    {
        TSNode startNode = ts_node_child_by_field_name(*exprNode, "start"s);
        TSNode stepNode = ts_node_child_by_field_name(*exprNode, "step"s);
        TSNode endNode = ts_node_child_by_field_name(*exprNode, "end"s);

        std::string start = state->getChunk(&startNode);

        std::string step;
        // default step is 1
        if (not ts_node_is_null(stepNode))
            step = state->getChunk(&stepNode);
        else
            step = "1";

        std::string end = state->getChunk(&endNode);

        start = bothEndsReplace(start, ' ');
        step = bothEndsReplace(step, ' ');
        end = bothEndsReplace(end, ' ');

        Number startN(start);
        Number stepN(step);
        Number endN(end);

        std::vector<Number> row;
        // include end as well
        for (Number i = startN; i <= endN; i += stepN)
            row.emplace_back(i);

        Matrix mat({ row });
        return STP_Value(STP_TypeID::MATRIX_2D, mat);
    }
} // namespace steppable::parser
