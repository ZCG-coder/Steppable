#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#define SDL_MAIN_USE_CALLBACKS 1
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "imgui.h"
#include "include/guiUtils.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct AppState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool redraw = true;
    bool imgui_initialized = false;
};

SDL_AppResult SDL_AppInit(void** appstate, int /*unused*/, char** /*unused*/)
{
    *appstate = SDL_malloc(sizeof(AppState));
    if (appstate == nullptr)
        return SDL_APP_FAILURE;
    auto* state = static_cast<AppState*>(*appstate);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        return SDL_APP_FAILURE;

    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    state->window = SDL_CreateWindow(nullptr,
                                     (int)(500 * main_scale),
                                     (int)(500 * main_scale),
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
    style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling,
                                     // changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(state->window, state->renderer);
    ImGui_ImplSDLRenderer3_Init(state->renderer);
    state->imgui_initialized = true;

    state->redraw = true;
    loadFonts(&io);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    auto* state = static_cast<AppState*>(appstate);
    if (!state->imgui_initialized)
        return SDL_APP_FAILURE;

    if (state->redraw)
    {
        // Start new ImGui frame
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();

        // Your ImGui UI
        ImGui::Begin("Hello, ImGui!");
        int win_w = 0;
        int win_h = 0;
        int drawable_w = 0;
        int drawable_h = 0;
        SDL_GetWindowSize(state->window, &win_w, &win_h); // logical (points)
        SDL_GetRenderOutputSize(state->renderer, &drawable_w, &drawable_h); // physical (pixels)

        ImGuiIO& io = ImGui::GetIO();
        io.DisplayFramebufferScale = ImVec2(static_cast<float>(drawable_w) / static_cast<float>(win_w),
                                            static_cast<float>(drawable_h) / static_cast<float>(win_h));
        ImGui::Text("Window size: %d x %d", win_w, win_h);
        ImGui::End();

        ImGui::ShowDemoWindow();

        ImGui::Render();

        // Clear SDL_Renderer
        SDL_SetRenderScale(state->renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(state->renderer, 16, 16, 16, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(state->renderer);

        // Render ImGui
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), state->renderer);

        SDL_RenderPresent(state->renderer);
        state->redraw = false;
    }
    SDL_Delay(1);
    return SDL_APP_CONTINUE;
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
    if (state->imgui_initialized)
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        state->imgui_initialized = false;
    }
    if (result == SDL_APP_FAILURE)
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), (appstate != nullptr) ? state->window : NULL);
    if (state != nullptr)
        SDL_free(state);
}
