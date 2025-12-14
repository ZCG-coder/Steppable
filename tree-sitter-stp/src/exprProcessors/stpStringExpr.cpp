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
#include "stpInterp/stpExprHandler.hpp"

using namespace std::literals;

namespace steppable::parser
{
    STP_Value STP_handleStringExpr(const TSNode* exprNode, const STP_InterpState& state)
    {
        // String
        std::string data;
        for (uint32_t i = 0; i < ts_node_child_count(*exprNode); i++)
        {
            auto childNode = ts_node_child(*exprNode, i);
            const std::string childNodeType = ts_node_type(childNode);

            if (childNodeType == "string_char")
                data += state->getChunk(&childNode);
            else if (childNodeType == "unicode_escape")
            {
                auto hexDigitsNode = ts_node_named_child(childNode, 0);
                const std::string hexCode = state->getChunk(&hexDigitsNode);

                unsigned long codePoint = std::stoul(hexCode, nullptr, 16);
                std::string text = stringUtils::unicodeToUtf8(static_cast<int>(codePoint));
                data += text;
            }
            else if (childNodeType == "octal_escape")
            {
                std::string octDigits = state->getChunk(&childNode);
                octDigits.erase(octDigits.begin()); // Erase leading '\' character

                unsigned long codePoint = std::stoul(octDigits, nullptr, 8);
                std::string text = stringUtils::unicodeToUtf8(static_cast<int>(codePoint));
                data += text;
            }
            else if (childNodeType == "formatting_snippet")
            {
                auto formatExprNode = ts_node_child_by_field_name(childNode, "formatting_expr"s);
                STP_Value value = STP_handleExpr(&formatExprNode, state, false, "");

                data += value.present("", false);
            }
        }

        return STP_Value(STP_TypeID::STRING, data);
    }
} // namespace steppable::parser
