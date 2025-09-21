#include "steppable/stpArgSpace.hpp"

#include "output.hpp"
#include "platform.hpp"

#include <utility>

using namespace steppable::__internals::utils;
using namespace std::literals;

namespace steppable::parser
{
    template<>
    std::any STP_ArgContainer::getArgValue<std::string>(const std::string& argName) const
    {
        // Find argument by name
        for (const auto& arg : arguments)
            if (arg.name == argName)
                return arg.value;
        // Not found: fall back to default from constraint
        for (const auto& cons : constraints)
            if (cons.requiredName == argName)
                return cons.defaultVal;
        throw std::out_of_range("Argument name not found in constraints");
    }

    template<>
    std::any STP_ArgContainer::getArgValue<int>(const int& idx) const
    {
        if (idx >= 0 and std::cmp_less(idx, arguments.size()))
            return arguments[idx].value;
        if (idx >= 0 and std::cmp_less(idx, constraints.size()))
            return constraints[idx].defaultVal;
        throw std::out_of_range("Positional index out of range of constraints");
    }

    STP_ArgContainer* STP_castToArgList(void* data) { return static_cast<STP_ArgContainer*>(data); }

    void STP_ArgContainer::checkArgs(const std::vector<STP_ArgumentConstraint>& constraints) const
    {
        // Partition constraints
        std::vector<const STP_ArgumentConstraint*> positionalConstraints;
        std::unordered_map<std::string, const STP_ArgumentConstraint*> keywordConstraints;
        for (const auto& c : constraints)
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
            output::error("runtime"s, "Not enough positional arguments provided."s, {});
            programSafeExit(1);
        }
        for (std::size_t i = 0; i < positionalConstraints.size(); ++i)
        {
            const auto* constraint = positionalConstraints[i];
            if (const auto* arg = positionalArgs[i]; arg->typeID != constraint->valueType)
            {
                output::error("runtime"s, "Positional argument type mismatch at position {0}"s, { std::to_string(i) });
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
                    output::error("runtime"s, "Keyword argument '{0}' type mismatch."s, { name });
                    programSafeExit(1);
                }
            }
        }
    }
} // namespace steppable::parser