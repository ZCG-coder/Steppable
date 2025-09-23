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

#include "stpTypeName.hpp"

#include <any>
#include <string>
#include <vector>

namespace steppable::parser
{
    struct STP_Argument
    {
        std::string name;

        std::any value;
        STP_TypeID typeID;

        STP_Argument(std::string name, std::any value, const STP_TypeID& typeID);
    };

    struct STP_ArgumentConstraint
    {
        std::string requiredName;
        STP_TypeID valueType;

        std::any defaultVal;
    };

    class STP_ArgContainer
    {
        std::vector<STP_Argument> arguments;
        std::vector<STP_ArgumentConstraint> constraints;

    public:
        [[nodiscard]] bool isLoaded() const { return not arguments.empty(); }

        void checkArgs(const std::vector<STP_ArgumentConstraint>& argumentConstraints) const;

        explicit STP_ArgContainer(const std::vector<STP_Argument>& args,
                                  const std::vector<STP_ArgumentConstraint>& constraints) :
            arguments(args), constraints(constraints)
        {
            checkArgs(constraints);
        }

        template<typename ItemT>
        std::any getArgValue(const ItemT&) const;

        template<>
        // ReSharper disable CppExplicitSpecializationInNonNamespaceScope
        [[nodiscard]] std::any getArgValue<std::string>(const std::string& argName) const;

        template<>
        [[nodiscard]] std::any getArgValue<int>(const int& idx) const;
        // ReSharper restore CppExplicitSpecializationInNonNamespaceScope
    };

    struct STP_ValuePrimitive
    {
        std::string typeName;
        STP_TypeID typeID;

        std::any data;

        explicit STP_ValuePrimitive(const STP_TypeID& type, std::any data = {});

        [[nodiscard]] std::string present(const std::string& name, bool longFormat = true) const;
    };

    using STP_ArgumentConstraintList = std::vector<STP_ArgumentConstraint>;

    [[nodiscard]] STP_ArgContainer* STP_castToArgList(void* data);
} // namespace steppable::parser