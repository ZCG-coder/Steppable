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

        void checkArgs(const std::vector<STP_ArgumentConstraint>& constraints) const;

        explicit STP_ArgContainer(const std::vector<STP_Argument>& args,
                                  const std::vector<STP_ArgumentConstraint>& constraints) :
            arguments(args), constraints(constraints)
        {
            checkArgs(constraints);
        }

        template<typename ItemT>
        std::any getArgValue(const ItemT&) const;

        template<>
        [[nodiscard]] std::any getArgValue<std::string>(const std::string& argName) const;

        template<>
        [[nodiscard]] std::any getArgValue<int>(const int& idx) const;
    };

    using STP_ArgumentConstraintList = std::vector<STP_ArgumentConstraint>;

    [[nodiscard]] STP_ArgContainer* STP_castToArgList(void* data);
} // namespace steppable::parser