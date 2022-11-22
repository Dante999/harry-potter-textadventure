#include "window_rooms.hpp"

#include "hpta_imgui.hpp"
#include "utils.hpp"

static constexpr size_t MAXLEN_DESCRIPTION = 1024;
static constexpr size_t MAXLEN_NAME        = 255;
static constexpr size_t MAXLEN_ID          = 255;

namespace {
struct UI_exit {
    char direction[50];
    char description[255];
    char room_id[255];
};

struct UI_item {
    int  quantity;
    char id[255];
};

struct UI_room {
    char id[255];
    char name[255];
    char description[1024];
};

struct UI_detail {
    char name[255];
    char description[1024];
};

struct UI_secret {
    char name[MAXLEN_NAME];
    char description_before_reveal[MAXLEN_DESCRIPTION];
    char description_after_reveal[MAXLEN_DESCRIPTION];
    char text_on_reveal[MAXLEN_DESCRIPTION];
    char needs_spell_id[MAXLEN_ID];
    char needs_item_id[MAXLEN_ID];
    char needs_password[MAXLEN_NAME];
    char reveals_item_id[MAXLEN_ID];
};

static UI_room                g_room;
static std::vector<UI_exit>   g_exits;
static std::vector<UI_item>   g_items;
static std::vector<UI_detail> g_details;
static std::vector<UI_secret> g_secrets;

static void show_popup_edit_secret(UI_secret &secret)
{
    ImGui::PushID(secret.name);
    ImGui::PushItemWidth(hpta_imgui::get_textwrapwidth());
    ImGui::InputText("Name", secret.name, std::size(secret.name));
    ImGui::InputText("needs spell id", secret.needs_spell_id, std::size(secret.needs_spell_id));
    ImGui::InputText("needs item id", secret.needs_item_id, std::size(secret.needs_item_id));
    ImGui::InputText("needs password", secret.needs_password, std::size(secret.needs_password));
    ImGui::InputText("reveals item id", secret.reveals_item_id, std::size(secret.reveals_item_id));
    hpta_imgui::InputTextMultilineWrapped("Description before reveal", secret.description_before_reveal,
                                          std::size(secret.description_before_reveal));
    hpta_imgui::InputTextMultilineWrapped("Description after reveal", secret.description_after_reveal,
                                          std::size(secret.description_after_reveal));
    hpta_imgui::InputTextMultilineWrapped("Text on reveal", secret.text_on_reveal, std::size(secret.text_on_reveal));
    ImGui::PopItemWidth();
    ImGui::PopID();
}

} // namespace

void Window_Rooms::create_object()
{
    m_current_object = Room{"/rooms/unknown.json"};

    m_current_object.set_name("no name");
    m_current_object.set_description("no description");
}

void Window_Rooms::load_object()
{
    strncpy(g_room.id, m_current_object.get_id().c_str(), sizeof(g_room.id) - 1);
    strncpy(g_room.name, m_current_object.get_name().c_str(), sizeof(g_room.name) - 1);
    strncpy(g_room.description, utils::wrap_text(m_current_object.get_description()).c_str(),
            sizeof(g_room.description) - 1);

    g_exits.clear();
    for (const auto &exit : m_current_object.get_exits()) {
        UI_exit ui_exit;

        strncpy(ui_exit.direction, exit.direction.c_str(), sizeof(ui_exit.direction));
        strncpy(ui_exit.description, exit.description.c_str(), sizeof(ui_exit.description));
        strncpy(ui_exit.room_id, exit.room_id.c_str(), sizeof(ui_exit.room_id));

        g_exits.emplace_back(ui_exit);
    }

    g_secrets.clear();
    for (const auto &secret : m_current_object.get_secrets()) {
        UI_secret ui_secret;

        strncpy(ui_secret.name, secret.name.c_str(), sizeof(ui_secret.name));
        strncpy(ui_secret.description_before_reveal, secret.description_before_reveal.c_str(),
                sizeof(ui_secret.description_before_reveal));
        strncpy(ui_secret.description_after_reveal, secret.description_after_reveal.c_str(),
                sizeof(ui_secret.description_after_reveal));
        strncpy(ui_secret.text_on_reveal, secret.text_on_reveal.c_str(), sizeof(ui_secret.text_on_reveal));
        strncpy(ui_secret.needs_spell_id, secret.needs_spell_id.c_str(), sizeof(ui_secret.needs_spell_id));
        strncpy(ui_secret.needs_item_id, secret.needs_item_id.c_str(), sizeof(ui_secret.needs_item_id));
        strncpy(ui_secret.needs_password, secret.needs_password.c_str(), sizeof(ui_secret.needs_password));
        strncpy(ui_secret.reveals_item_id, secret.reveals_item_id.c_str(), sizeof(ui_secret.reveals_item_id));

        g_secrets.emplace_back(ui_secret);
    }
}

std::vector<Room> Window_Rooms::get_objects() { return m_room_cache.get_list(); }

void Window_Rooms::refresh_cache() { m_room_cache.refresh(); }

void Window_Rooms::save_object()
{
    m_current_object.set_id(g_room.id);
    m_current_object.set_name(g_room.name);
    m_current_object.set_description(Hpta_strings::trim(Hpta_strings::remove_newlines(g_room.description)));

    std::vector<Room::Exit> exits;
    for (const auto &ui_exit : g_exits) {
        Room::Exit exit;

        exit.room_id     = ui_exit.room_id;
        exit.direction   = ui_exit.direction;
        exit.description = ui_exit.description;

        exits.emplace_back(exit);
    }
    m_current_object.set_exits(exits);

    persistency::save_room(Hpta_config::get_string(Settings::gamedata_dir), m_current_object);

    m_event_engine.publish(Event{Event::Type::ROOM_CHANGED, m_current_object.get_id(), ""});
}

void Window_Rooms::show_attributes()
{
    ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.20f);
    ImGui::InputText("ID", g_room.id, std::size(g_room.id));
    ImGui::InputText("Name", g_room.name, std::size(g_room.name));
    hpta_imgui::InputTextMultilineWrapped("Description", g_room.description, std::size(g_room.description));
    ImGui::PopItemWidth();

    ImGui::BeginTabBar("tabs");

    if (ImGui::BeginTabItem("Exits")) {
        show_tab_room_exits();
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Secrets")) {
        show_tab_room_secrets();
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
}

void Window_Rooms::show_tab_room_exits()
{

    ImGui::BeginTable("Directions", 4, ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders);

    ImGui::TableSetupColumn("Action##directions");
    ImGui::TableSetupColumn("Direction##directions");
    ImGui::TableSetupColumn("Description##directions");
    ImGui::TableSetupColumn("Room##directions");

    ImGui::TableHeadersRow();

    int i = 0;
    for (auto itr = g_exits.begin(); itr != g_exits.end(); ++itr) {
        ImGui::PushID(itr->direction);

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(-1);
        const auto delete_pressed = ImGui::Button("Delete");
        ImGui::PopItemWidth();

        if (delete_pressed) {
            g_exits.erase(itr);
        }
        else {

            ImGui::TableNextColumn();
            ImGui::PushItemWidth(-1);
            ImGui::InputText("##direction", itr->direction, std::size(itr->direction));
            ImGui::PopItemWidth();

            ImGui::TableNextColumn();
            ImGui::PushItemWidth(-1);
            ImGui::InputText("##description", itr->description, std::size(itr->description));
            ImGui::PopItemWidth();

            ImGui::TableNextColumn();
            ImGui::PushItemWidth(-1);
            ImGui::InputText("##room_id", itr->room_id, std::size(itr->room_id));
            ImGui::PopItemWidth();

            if (ImGui::BeginDragDropTarget()) {
                ImGuiDragDropFlags target_flags = 0;

                target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("ROOM_ID", target_flags)) {
                    strncpy(itr->room_id, static_cast<const char *>(payload->Data), std::size(itr->room_id));
                }
                ImGui::EndDragDropTarget();
            }
        }

        ImGui::PopID();

        ImGui::TableNextRow();
        ++i;
    }

    ImGui::EndTable();

    if (ImGui::Button("Add Exit")) {
        UI_exit exit{"", "", ""};

        g_exits.emplace_back(exit);
    }
}

void Window_Rooms::show_tab_room_secrets()
{
    ImGui::BeginTable("Secrets", 6, ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders);

    ImGui::TableSetupColumn("Action##secrets");
    ImGui::TableSetupColumn("Name##secrets");
    ImGui::TableSetupColumn("Needs item##secrets");
    ImGui::TableSetupColumn("Needs password##secrets");
    ImGui::TableSetupColumn("Needs spell##secrets");
    ImGui::TableSetupColumn("Reveals item##secrets");
    ImGui::TableHeadersRow();

    for (auto &ui_secret : g_secrets) {
        ImGui::PushID(ui_secret.name);
        ImGui::TableNextRow();

        ImGui::TableNextColumn();
        if (ImGui::Button("Edit"))
            ImGui::OpenPopup(ui_secret.name);

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal(ui_secret.name, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            if (ImGui::Button("Close")) {
                ImGui::CloseCurrentPopup();
            }
            show_popup_edit_secret(ui_secret);

            ImGui::EndPopup();
        }

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.name);

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.needs_item_id);

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.needs_password);

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.needs_spell_id);

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.reveals_item_id);

        ImGui::PopID();
    }

    ImGui::EndTable();
}
