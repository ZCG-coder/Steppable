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

#include "output.hpp"
#include "stpInterp/stpInit.hpp"
#include "util.hpp"

#include <cmath>

using namespace std::literals;

namespace steppable::parser
{
    using namespace steppable;

    bool STP_checkRecursiveNodeSanity(const TSNode& node, const STP_InterpState& state)
    {
        if (ts_node_is_null(node))
            return false;

        if (ts_node_is_error(node) or ts_node_is_missing(node))
        {
            STP_throwSyntaxError(node, state);
            return true;
        }

        for (uint32_t i = 0; i < ts_node_child_count(node); i++)
        {
            TSNode child = ts_node_child(node, i);
            if (STP_checkRecursiveNodeSanity(child, state))
                return true;
        }

        return false;
    }

    void STP_throwError(const TSNode& node, const STP_InterpState& state, const std::string& reason)
    {
        output::error("parser"s, reason);

        auto [startRow, startCol] = ts_node_start_point(node);
        auto [endRow, endCol] = ts_node_end_point(node);

        output::error("parser"s,
                      "At {0} : Ln {1}, Col {2}"s,
                      {
                          state->getFile(),
                          std::to_string(startRow + 1),
                          std::to_string(startCol),
                      });
        std::string errorChunk = state->getChunk();
        auto lines = stringUtils::split(errorChunk, '\n');
        lines.erase(lines.begin(), lines.begin() + startRow);
        lines.erase(lines.begin() + (endRow - startRow + 1), lines.end());

        const auto& endLineLen = static_cast<size_t>(log10(endRow + 1) + 1);
        const auto& startLineLen = static_cast<size_t>(log10(startRow + 1) + 1);
        const size_t& padding = std::max(startLineLen, endLineLen);

        for (size_t i = 0; i < lines.size(); i++)
        {
            const auto& line = lines.at(i);
            std::string lineNo = stringUtils::lPad(std::to_string(startRow + i + 1), padding);
            std::string indicators = std::string(startCol, ' ') + std::string(endCol - startCol, '~');
            output::info("parser"s,
                         "{0}  | {1}"s,
                         {
                             lineNo,
                             line,
                         });
            output::info("parser"s, "{0}  | {1}"s, { std::string(lineNo.length(), ' '), indicators });
        }

        if (not state->isInteractive())
            utils::programSafeExit(1);
    }

    void STP_throwSyntaxError(const TSNode& node, const STP_InterpState& state)
    {
        STP_throwError(node, state, "Syntax error"s);
    }
} // namespace steppable::parser
