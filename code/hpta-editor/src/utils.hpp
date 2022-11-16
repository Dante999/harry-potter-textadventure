#ifndef IMGUI_HELPER_HPP
#define IMGUI_HELPER_HPP

#include <imgui.h>

namespace utils {

// static constexpr size_t column_width = 80;

inline float calc_textwidth(size_t text_length)
{
    const float fontsize = ImGui::GetFontSize();
    const float textlen  = static_cast<float>(text_length);
    const float scale    = 1;

    return (fontsize * scale) * textlen;
}

inline std::string wrap_text(std::string text)
{
    return Hpta_strings::add_newline_on_column_width(Hpta_strings::remove_newlines(text),
                                                     Hpta_config::get_uint(Settings::editor_textwraplen));
}

inline bool InputTextMultilineWrapped(const char *label, char *buf, size_t buf_size, const ImVec2 &size = ImVec2(0, 0),
                                      ImGuiInputTextFlags flags = 0)
{
    flags |= ImGuiInputTextFlags_CallbackEdit;

    auto on_text_edit = [](ImGuiInputTextCallbackData *data) -> int {
        if (data->EventFlag != ImGuiInputTextFlags_CallbackEdit) {
            return 0;
        }

        const size_t column_width = static_cast<size_t>(Hpta_config::get_uint(Settings::editor_textwraplen));

        if (static_cast<size_t>(data->BufTextLen) % (column_width + 1) == 0) {

            auto text = utils::wrap_text(data->Buf);

            strncpy(data->Buf, text.c_str(), static_cast<size_t>(data->BufSize));
            data->BufTextLen = static_cast<int>(strlen(data->Buf));

            data->BufDirty = true;
        }

        return 0;
    };

    return ImGui::InputTextMultiline(label, buf, buf_size, size, flags, on_text_edit);
}

} // namespace utils

#endif /* IMGUI_HELPER_HPP */
