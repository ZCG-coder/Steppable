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

#include "steppable/stpTypeName.hpp"
#include "stpInterp/stpBetterTS.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpStore.hpp"

using namespace std::literals;

namespace steppable::parser
{
    void STP_handleSymbolDeclStmt(const TSNode* node, const STP_InterpState& state)
    {
        TSNode nameNode = ts_node_child_by_field_name(*node, "sym_name"s);
        const std::string& name = state->getChunk(&nameNode);

        STP_Value assignmentVal(STP_TypeID::SYMBOL);
        assignmentVal.data = name;
        assignmentVal.typeName = STP_typeNames.at(STP_TypeID::SYMBOL);
        state->getCurrentScope()->addVariable(name, assignmentVal);
    }
} // namespace steppable::parser