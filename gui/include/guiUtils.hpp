#include "imgui.h"

#include <string>

void addFontIfExistent(const ImGuiIO* io,
                       const std::string& path,
                       const ImFontConfig* config,
                       const ImWchar* ranges) noexcept;

void loadFonts(const ImGuiIO* io) noexcept;
