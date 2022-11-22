#ifndef HPTA_IMGUI_HPP
#define HPTA_IMGUI_HPP

#include <string>

#include <imgui.h>
#include <imgui_stdlib.h>

#include "hpta-lib/util/hpta_config.hpp"
#include "settings.hpp"

namespace hpta_imgui {

inline float get_textwrapwidth()
{
    return ImGui::GetFontSize() * Hpta_config::get_float(Settings::editor_fontsize_ratio) *
           Hpta_config::get_float(Settings::editor_textwraplen);
}

bool InputTextMultilineWrapped(const char *label, char *buf, size_t buf_size, const ImVec2 &size = ImVec2(0, 0),
                               ImGuiInputTextFlags flags = 0);

} // namespace hpta_imgui

#endif /* HPTA_IMGUI_HPP */
