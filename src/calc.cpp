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

#include "fn/calc.hpp"

#include "steppable/stpArgSpace.hpp"

using namespace steppable::parser;
using namespace steppable::__internals;

STP_EXPORT_FUNC(STP_cos)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::cos(number.present(), number.getDecimals(), 0);
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_sin)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::sin(number.present(), number.getDecimals(), 0);
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_tan)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::tan(number.present(), number.getDecimals(), 0);
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_asin)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::asin(number.present(), number.getDecimals(), 0);
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_acos)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::acos(number.present(), number.getDecimals(), 0);
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_atan)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::atan(number.present(), number.getDecimals(), 0);
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_cosh)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::cosh(number.present(), number.getDecimals());
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_sinh)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::sinh(number.present(), number.getDecimals());
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_tanh)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::tanh(number.present(), number.getDecimals());
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_acosh)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::acosh(number.present(), number.getDecimals());
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_asinh)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::asinh(number.present(), number.getDecimals());
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}

STP_EXPORT_FUNC(STP_atanh)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    const auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    const steppable::Number res = calc::atanh(number.present(), number.getDecimals());
    return new STP_ValuePrimitive(STP_TypeID_NUMBER, res);
}
