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
#include "steppable/number.hpp"
#include "steppable/stpArgSpace.hpp"
#include "stpInterp/stpBetterTS.hpp"
#include "stpInterp/stpErrors.hpp"
#include "stpInterp/stpExprHandler.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpStore.hpp"

#include <cassert>
#include <cstdint>

using namespace std::literals;

namespace steppable::parser
{
    STP_Value STP_handleMatrixExpr(const TSNode* exprNode, const STP_InterpState& state)
    {
        // Matrix
        std::unique_ptr<size_t> lastColLength;
        MatVec2D<Number> matVec;
        for (uint32_t j = 0; j < ts_node_child_count(*exprNode); j++)
        {
            TSNode node = ts_node_child(*exprNode, j);
            if (const std::string& nodeType = ts_node_type(node);
                nodeType != "matrix_row" and nodeType != "matrix_row_last")
                continue;

            size_t currentCols = 0;
            std::vector<Number> currentMatRow;
            for (uint32_t i = 0; i < ts_node_child_count(node); i++)
            {
                TSNode cell = ts_node_child(node, i);
                if (ts_node_type(cell) == ";"s)
                    continue;
                STP_Value val = STP_handleExpr(&cell, state);

                if (val.typeID != STP_TypeID::NUMBER)
                    STP_throwError(cell, state, "Matrix should contain numbers only."s);

                auto value = std::any_cast<Number>(val.data);
                currentMatRow.emplace_back(value);
                currentCols++;
            }

            if (lastColLength)
            {
                if (currentCols != *lastColLength)
                    STP_throwError(node, state, "Matrix should contain numbers only."s);
            }
            matVec.emplace_back(currentMatRow);
            lastColLength = std::make_unique<size_t>(currentCols);
        }

        Matrix data(matVec);
        return STP_Value(STP_TypeID::MATRIX_2D, data);
    }
} // namespace steppable::parser
