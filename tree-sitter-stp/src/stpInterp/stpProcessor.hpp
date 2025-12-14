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
     * @brief Recursively process all children nodes inside a root node.
     *
     * @param parent The parent node containing all children nodes.
     * @param stpState The current state of the interpreter.
     * @param createNewScope Whether to create a new scope to run all statements within.
     */
    void STP_processChunkChild(const TSNode& parent, const STP_InterpState& stpState, bool createNewScope = false);

    // Statement processors

    /**
     * @brief Handle an assignment statement.
     *
     * @param node The assignment statement node.
     * @param state The current state of the interpreter.
     */
    void STP_handleAssignment(const TSNode* node, const STP_InterpState& state = nullptr);

    /**
     * @brief Handle an if-else statement.
     *
     * @param node The assignment statement node.
     * @param state The current state of the interpreter.
     */
    void STP_processIfElseStmt(const TSNode* node, const STP_InterpState& state);

    /**
     * @brief Handle an symbol declaration statement.
     *
     * @param node The symbol declaration node.
     * @param state The current state of the interpreter.
     */
    void STP_handleSymbolDeclStmt(const TSNode* node, const STP_InterpState& state);

    /**
     * @brief Process a function declaration statement.
     *
     * @param node The function declaration node.
     * @param state The current state of the interpreter.
     */
    void STP_processFuncDefinition(const TSNode* node, const STP_InterpState& state);

    void STP_processWhileStmt(const TSNode* node, const STP_InterpState& state);
} // namespace steppable::parser
