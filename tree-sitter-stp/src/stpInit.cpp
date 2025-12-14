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

#include "stpInterp/stpInit.hpp"

#include "constants.hpp"
#include "stpInterp/stpStore.hpp"

#include <memory>
#include <stdexcept>

using namespace std::literals;

namespace steppable::parser
{
    const auto _storage = std::make_shared<STP_InterpStoreLocal>();

    void STP_init()
    {
        _storage->getGlobalScope()->addVariable("pi", STP_Value(STP_TypeID::NUMBER, Number(constants::PI), true));
        _storage->getGlobalScope()->addVariable("e", STP_Value(STP_TypeID::NUMBER, Number(constants::E), true));
    }

    const STP_InterpState& STP_getState() { return _storage; }

    int STP_destroy()
    {
        if (_storage == nullptr)
            throw std::runtime_error("Uninitialized state is destroyed.");
        return 0;
    }
} // namespace steppable::parser
