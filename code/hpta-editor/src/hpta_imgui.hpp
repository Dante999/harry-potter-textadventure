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

bool InputText(const char *label, std::string &buf, ImGuiInputTextFlags flags = 0);

bool InputTextMultilineWrapped(const char *label, std::string &buf, const ImVec2 &size = ImVec2(0, 0),
                               ImGuiInputTextFlags flags = 0);

bool InputTextWithSelectableList(const char *label, std::string &buf, std::vector<std::string> selectable,
                                 const ImVec2 &size = ImVec2(0, 0));

} // namespace hpta_imgui

#endif /* HPTA_IMGUI_HPP */
