#include <functional>
#ifndef WINDOWS
    #include <csignal>
#else
    #include <windows.h>
#endif

namespace steppable::parser
{
    static std::function<void(void)> handler;
#ifdef WINDOWS
    static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
    {
        if (fdwCtrlType == CTRL_C_EVENT)
        {
            if (handler)
                handler();
            return TRUE;
        }
        return FALSE;
    }

#endif

    void STP_addCtrlCHandler(const std::function<void(void)>& predicate)
    {
#ifdef WINDOWS
        handler = predicate;
        SetConsoleCtrlHandler(CtrlHandler, TRUE);
#else
        handler = predicate;
        (void)std::signal(SIGINT, [](int) {
            if (handler)
                handler();
        });
#endif
    }
} // namespace steppable::parser