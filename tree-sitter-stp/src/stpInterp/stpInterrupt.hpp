#include <functional>

namespace steppable::parser
{
    void STP_addCtrlCHandler(const std::function<void(void)>& predicate);
}