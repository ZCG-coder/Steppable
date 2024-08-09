#include "gui.hpp"
#include "imgui.h"

#include <SDL.h>
#include <SDL_opengl.h>

// NOTE TO DEVELOPERS: This file is a test file for the GUI module of the Steppable library.
//                     When building the GUI part for the first time, this can come in handy.
//                     Run the executable to see if the GUI window works.

using namespace steppable;
using namespace steppable::gui::__internals;

void setUpContents()
{
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    ImGui::End();
}

int main() { gui::runWindow("", &setUpContents); }
