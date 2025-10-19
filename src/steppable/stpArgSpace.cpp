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

#include "steppable/stpArgSpace.hpp"

#include "output.hpp"
#include "platform.hpp"
#include "steppable/mat2d.hpp"
#include "steppable/number.hpp"

#include <sstream>
#include <string>
#include <utility>

using namespace steppable::__internals::utils;
using namespace std::literals;

namespace steppable::parser
{
    STP_ArgContainer* STP_castToArgList(void* data) { return static_cast<STP_ArgContainer*>(data); }

    STP_Argument::STP_Argument(std::string name, std::any value, const STP_TypeID& typeID) :
        name(std::move(name)), value(std::move(value)), typeID(typeID)
    {
    }

    std::string STP_ArgContainer::checkArgs(const std::vector<STP_ArgumentConstraint>& argumentConstraints) const
    {
        // Partition constraints
        std::vector<const STP_ArgumentConstraint*> positionalConstraints;
        std::unordered_map<std::string, const STP_ArgumentConstraint*> keywordConstraints;
        for (const auto& c : argumentConstraints)
            if (c.requiredName.empty())
                positionalConstraints.push_back(&c);
            else
                keywordConstraints[c.requiredName] = &c;

        // Partition arguments
        std::vector<const STP_Argument*> positionalArgs;
        std::unordered_map<std::string, const STP_Argument*> keywordArgs;
        for (const auto& arg : arguments)
            if (arg.name.empty())
                positionalArgs.push_back(&arg);
            else
                keywordArgs[arg.name] = &arg;

        // Check positional arguments
        if (positionalArgs.size() < positionalConstraints.size())
        {
            return __internals::format::format("Not enough positional arguments provided."s, {});
            programSafeExit(1);
        }
        for (std::size_t i = 0; i < positionalConstraints.size(); ++i)
        {
            const auto* constraint = positionalConstraints[i];
            if (const auto* arg = positionalArgs[i]; arg->typeID != constraint->valueType)
            {
                return __internals::format::format("Positional argument type mismatch at position {0}"s,
                                                   { std::to_string(i) });
                programSafeExit(1);
            }
        }

        // Check keyword arguments
        for (const auto& [name, constraint] : keywordConstraints)
        {
            if (keywordArgs.contains(name))
            {
                if (const auto* arg = keywordArgs[name]; arg->typeID != constraint->valueType)
                {
                    return __internals::format::format("Keyword argument '{0}' type mismatch."s, { name });
                    programSafeExit(1);
                }
            }
        }

        return "";
    }

    STP_ValuePrimitive::STP_ValuePrimitive(const STP_TypeID& type, std::any data, std::string error) :
        typeName(STP_typeNames.at(type)), typeID(type), error(std::move(error)), data(std::move(data))
    {
    }

    std::string STP_ValuePrimitive::present(const std::string& name, const bool longFormat) const
    {
        std::stringstream ret;
        std::string presented;

        if (longFormat)
        {
            ret << name << "(" << typeName << ")";
            ret << "\n";
        }

        switch (typeID)
        {
        case STP_TypeID::NUMBER:
            presented = std::any_cast<Number>(data).present();
            break;
        case STP_TypeID::MATRIX_2D:
            presented = std::any_cast<Matrix>(data).present();
            break;
        case STP_TypeID::STRING:
            presented = "\"" + std::any_cast<std::string>(data) + "\"";
            break;
        default:
            break;
        }

        if (longFormat)
        {
            std::string line;
            std::istringstream iss(presented);
            while (getline(iss, line))
                ret << "    " << line << "\n";
        }
        else
            ret << presented;

        return ret.str();
    }
} // namespace steppable::parser
