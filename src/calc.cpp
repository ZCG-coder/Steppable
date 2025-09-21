#include "fn/calc.hpp"

#include "steppable/stpArgSpace.hpp"

using namespace steppable::parser;

STP_EXPORT_FUNC(STP_cos)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    std::cout << steppable::__internals::calc::cos(number.present(), 10, 0) << std::endl;
}

STP_EXPORT_FUNC(STP_sin)
{
    STP_ArgContainer* container = STP_castToArgList(argSpace);
    container->checkArgs({ { "", STP_TypeID_NUMBER } });

    auto number = std::any_cast<steppable::Number>(container->getArgValue(0));
    std::cout << steppable::__internals::calc::sin(number.present(), 10, 0) << std::endl;
}