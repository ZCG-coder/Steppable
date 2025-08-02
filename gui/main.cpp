#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL_init.h"
#include "include/appState.hpp"
#include "include/guiUtils.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <imgui.h>

using namespace steppable::__internals::gui;

SDL_AppResult SDL_AppInit(void** appstate, int /*unused*/, char** /*unused*/)
{
    *appstate = new AppState; // NOLINT(*-owning-memory)
    auto* state = static_cast<AppState*>(*appstate);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        return SDL_APP_FAILURE;

    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    state->window = SDL_CreateWindow(nullptr,
                                     static_cast<int>(500 * main_scale),
                                     static_cast<int>(500 * main_scale),
                                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (state->window == nullptr)
        return SDL_APP_FAILURE;
    state->renderer = SDL_CreateRenderer(state->window, nullptr);
    if (state->renderer == nullptr)
        return SDL_APP_FAILURE;
    SDL_SetRenderVSync(state->renderer, 1);

    // --- ImGui setup ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(state->window, state->renderer);
    ImGui_ImplSDLRenderer3_Init(state->renderer);
    state->imgui_initialized = true;

    state->redraw = true;
    loadAllFonts(state);

    io.Fonts->Build();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    auto* state = static_cast<AppState*>(appstate);
    if (!state->imgui_initialized)
        return SDL_APP_FAILURE;
    SDL_AppResult res = SDL_APP_CONTINUE;

    if (state->redraw)
    {
        // Start new ImGui frame
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();

        res = state->predicate();

        ImGui::Render();

        // Clear SDL_Renderer
        ImGuiIO& io = ImGui::GetIO();
        SDL_SetRenderScale(state->renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(state->renderer);

        // Render ImGui
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), state->renderer);

        SDL_RenderPresent(state->renderer);
        state->redraw = false;
    }
    SDL_Delay(1);
    return res;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    auto* state = static_cast<AppState*>(appstate);
    if (state->imgui_initialized)
        ImGui_ImplSDL3_ProcessEvent(event);

    // Redraw on any event that might affect ImGui
    if (event->type != SDL_EVENT_QUIT)
    {
        state->redraw = true;
        return SDL_APP_CONTINUE;
    }
    return SDL_APP_SUCCESS;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    auto* state = static_cast<AppState*>(appstate);
    assert(state != nullptr);

    if (state->imgui_initialized)
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        state->imgui_initialized = false;
    }
    if (result == SDL_APP_FAILURE)
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), state->window);

    SDL_free(state);
}
