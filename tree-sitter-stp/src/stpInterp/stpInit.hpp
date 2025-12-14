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

#include "stpInterp/stpStore.hpp"

#include <memory>

namespace steppable::parser
{
    using STP_InterpState = std::shared_ptr<STP_InterpStoreLocal>;
    extern const STP_InterpState _storage;

    void STP_init();

    /**
     * @brief Gets the current state of the interpreter.
     * @details If the state is not initialized yet, it will initialize it automatically.
     *
     * @return STP_InterpState A reference to the current state of the interpreter.
     */
    const STP_InterpState& STP_getState();

    /**
     * @brief Free the state pointer immediately. Call upon exit.
     *
     * @throw std::runtime_error If trying to free the pointer when it is unintialized.
     *
     * @return int Status of the free operation, now always 0.
     */
    int STP_destroy();
} // namespace steppable::parser
