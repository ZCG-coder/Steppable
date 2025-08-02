#pragma once

#include "SDL3/SDL_init.h"
#include "fontMgr.hpp"
#include "imgui_node_editor_internal.h"
#include "node.hpp"

#include <SDL3/SDL.h>
#include <imgui.h>
#include <random>
#include <string>

namespace steppable::__internals::nodes
{
} // namespace steppable::__internals::nodes

namespace steppable::__internals::gui
{
    using namespace steppable::__internals::nodes;
    namespace ed = ax::NodeEditor;

    struct AppState
    {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool redraw = true;
        bool imgui_initialized = false;

        std::string editingWorkspace;
        bool isEditingWorkspace = false;
        ed::Config config;
        ed::EditorContext* nodeEditorCtx;
        std::vector<Node<AppState>> nodes;
        std::map<int, std::pair<unsigned long, unsigned long>> links;

        FontManager fontMgr{};

        AppState();

        void showWorkspaceEditor();

        [[nodiscard]] SDL_AppResult predicate();
    };
} // namespace steppable::__internals::gui
