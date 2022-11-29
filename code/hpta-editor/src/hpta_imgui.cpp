#include "hpta_imgui.hpp"

#include <functional>

#include <spdlog/spdlog.h>

#include "hpta-lib/util/hpta_config.hpp"
#include "settings.hpp"
#include "utils.hpp"

namespace {

struct InputTextCallback_UserData {
    std::string *buf;
};

static int resize_callback(ImGuiInputTextCallbackData *data)
{
    InputTextCallback_UserData *user_data = static_cast<InputTextCallback_UserData *>(data->UserData);
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
        // TODO: is somehow called with each new char, even after resizing

        std::string *str = user_data->buf;
        IM_ASSERT(data->Buf == str->c_str());

        str->resize(static_cast<size_t>(data->BufTextLen));

        data->Buf = const_cast<char *>(str->c_str());
    }

    return 0;
}

static int textwrap_callback(ImGuiInputTextCallbackData *data)
{
    if (data->EventFlag != ImGuiInputTextFlags_CallbackEdit) {
        return 0;
    }

    utils::wrap_text(data->Buf, static_cast<size_t>(data->BufSize));

    data->BufTextLen = static_cast<int>(strlen(data->Buf));
    data->BufDirty   = true;

    return 0;
}

} // namespace

bool hpta_imgui::InputText(const char *label, std::string &buf, ImGuiInputTextFlags flags)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;

    cb_user_data.buf = &buf;

    char *buf_c = const_cast<char *>(buf.c_str());

    auto callback = [](ImGuiInputTextCallbackData *data) { return resize_callback(data); };

    return ImGui::InputText(label, buf_c, buf.capacity() + 1, flags, callback, &cb_user_data);
}

bool hpta_imgui::InputTextMultilineWrapped(const char *label, std::string &buf, const ImVec2 &size,
                                           ImGuiInputTextFlags flags)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= (ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_CallbackEdit);

    InputTextCallback_UserData cb_user_data;

    cb_user_data.buf = &buf;

    char *buf_c = const_cast<char *>(buf.c_str());

    auto callback = [](ImGuiInputTextCallbackData *data) {
        resize_callback(data);
        textwrap_callback(data);
        return 0;
    };

    // buf = utils::wrap_text(buf);

    return ImGui::InputTextMultiline(label, buf_c, buf.capacity() + 1, size, flags, callback, &cb_user_data);
}

bool hpta_imgui::InputTextWithSelectableList(const char *label, std::string &buf, std::vector<std::string> list,
                                             const ImVec2 &size)
{
#if 1
    const char *popup_id = "Select";

    ImGui::PushID(label);
    if (ImGui::Button(buf.c_str(), size )) {
        ImGui::OpenPopup(popup_id);
    }
    
    if( strncmp(label, "##", 2) != 0)
    {
        ImGui::SameLine();
        ImGui::TextUnformatted(label);
    }
    

    int current_index = -1;
    if (ImGui::BeginPopupModal(popup_id, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

        for (int i = 0; i < static_cast<int>(list.size()); i++) {

            const auto object = list.at(static_cast<size_t>(i));

            if (ImGui::Selectable(object.c_str(), current_index == i)) {
                current_index = i;
                buf           = object;
            }
        }

        ImGui::EndPopup();
    }
    ImGui::PopID();

    return true;

#else
    std::ignore = size;

    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;

    cb_user_data.buf = &buf;

    char *buf_c = const_cast<char *>(buf.c_str());

    auto callback = [](ImGuiInputTextCallbackData *data) { return resize_callback(data); };

    flags |= ImGuiInputTextFlags_ReadOnly;

    const char *popup_id = "Select";

    ImGui::PushID(label);

    ImGui::BeginGroup();
    ImGui::InputText("##textbox", buf_c, buf.capacity() + 1, flags, callback, &cb_user_data);

    ImGui::SameLine();
    if (ImGui::Button("...")) {
        ImGui::OpenPopup(popup_id);
    }

    ImGui::EndGroup();

    ImGui::SameLine();
    ImGui::TextUnformatted(label);

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    int current_index = -1;

    if (ImGui::BeginPopupModal(popup_id, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        // if (ImGui::Button("Close")) {
        //     ImGui::CloseCurrentPopup();
        // }

        for (int i = 0; i < static_cast<int>(list.size()); i++) {

            const auto object = list.at(static_cast<size_t>(i));

            if (ImGui::Selectable(object.c_str(), current_index == i)) {
                current_index = i;
                buf           = object;
            }
        }

        ImGui::EndPopup();
    }

    ImGui::PopID();

    return true;
#endif
}