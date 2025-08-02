#pragma once
#include "imgui.h"

#include <functional>
#include <string>

namespace steppable::__internals::gui
{
    struct OutPin
    {
        std::string name;
        ImVec4 color;

        int id = -1;
    };

    struct InPin
    {
        std::string name;
        ImVec4 color;

        unsigned long connectionFrom = 0; //< Output port ID that connected to this port.
        bool hasConnectionFrom = false;
        int id = -1;
    };

    template<typename ParentClass>
    struct Node
    {
        std::string name;
        std::string description;

        ImVec4 color;
        ImVec2 pos;

        std::vector<InPin> inputs;
        std::vector<OutPin> outputs;

        std::function<void(ParentClass* cls)> contentPredicate = [](ParentClass* /* unused */) {};
        int id = -1;
        bool deleted = false;
    };
} // namespace steppable::__internals::gui