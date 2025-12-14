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

#include "stpInterp/stpInit.hpp"

namespace steppable::parser
{
    /**
     * @brief Check for node "sanity", i.e., check for grammar compilance and syntax errors.
     *
     * @note When there is a syntax error, end the execution immediately. An error would have been printed to the
     * console already about this error.
     *
     * @param node The root node to start searching at.
     * @param state The current state of the interpreter.
     * @return true When there is a syntax error.
     * @return false When there are no errors.
     */
    bool STP_checkRecursiveNodeSanity(const TSNode& node, const STP_InterpState& state);

    /**
     * @brief Throws a syntax error.
     * @warning Syntax errors would not immediately stop the execution flow. Find errors with
     * `STP_checkRecursiveNodeSanity()` and then handle them.
     *
     * @param node The node containing the error.
     * @param state The current state of the interpreter.
     */
    void STP_throwSyntaxError(const TSNode& node, const STP_InterpState& state);

    /**
     * @brief Throw other kinds of errors.
     *
     * @param node The node containing the error.
     * @param state The current state of the interpreter.
     * @param reason The reason for the error.
     */
    void STP_throwError(const TSNode& node, const STP_InterpState& state, const std::string& reason);
} // namespace steppable::parser
