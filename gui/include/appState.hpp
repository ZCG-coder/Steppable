#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>

struct AppState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool redraw = true;
    bool imgui_initialized = false;

    void predicate() const
    {
        ImGui::Begin("Steppable");
        ImGui::Text("Hello world");
        ImGui::End();

        ImGui::ShowDemoWindow();
    }
};
