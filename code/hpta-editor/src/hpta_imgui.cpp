#include "hpta_imgui.hpp"

#include <spdlog/spdlog.h>

#include "hpta-lib/util/hpta_config.hpp"
#include "settings.hpp"
#include "utils.hpp"

bool hpta_imgui::InputTextMultilineWrapped(const char *label, char *buf, size_t buf_size, const ImVec2 &size,
                                           ImGuiInputTextFlags flags)
{
    flags |= ImGuiInputTextFlags_CallbackEdit;

    auto on_text_edit = [](ImGuiInputTextCallbackData *data) -> int {
        if (data->EventFlag != ImGuiInputTextFlags_CallbackEdit) {
            return 0;
        }

        utils::wrap_text(data->Buf, static_cast<size_t>(data->BufSize));

        data->BufTextLen = static_cast<int>(strlen(data->Buf));
        data->BufDirty   = true;

        return 0;
    };

    utils::wrap_text(buf, buf_size);

    return ImGui::InputTextMultiline(label, buf, buf_size, size, flags, on_text_edit);
}
