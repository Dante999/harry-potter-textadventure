#ifndef IMGUI_HELPER_HPP
#define IMGUI_HELPER_HPP

#include <imgui.h>

namespace utils {

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

inline const char *wrap_text(char *buf, size_t buf_size)
{
    auto text_wrapped = utils::wrap_text(buf);
    strncpy(buf, text_wrapped.c_str(), buf_size);
    return buf;
}

} // namespace utils

#endif /* IMGUI_HELPER_HPP */
