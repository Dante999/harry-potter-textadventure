#include "panel_rooms.hpp"

#include "hpta_imgui.hpp"
#include "utils.hpp"

namespace {
struct UI_exit {
    std::string direction;
    std::string description;
    std::string room_id;
};

struct UI_item {
    int         quantity;
    std::string id;
};

struct UI_room {
    std::string id;
    std::string name;
    std::string description;
};

struct UI_detail {
    std::string name;
    std::string description;
};

struct UI_secret {
    std::string name;
    std::string description_before_reveal;
    std::string description_after_reveal;
    std::string text_on_reveal;
    std::string needs_spell_id;
    std::string needs_item_id;
    std::string needs_password;
    std::string reveals_item_id;
};

static UI_room                g_room;
static std::vector<UI_exit>   g_exits;
static std::vector<UI_item>   g_items;
static std::vector<UI_detail> g_details;
static std::vector<UI_secret> g_secrets;

static void show_popup_edit_secret(UI_secret &secret)
{
    ImGui::PushID("edit_secret");
    ImGui::PushItemWidth(hpta_imgui::get_textwrapwidth());

    hpta_imgui::InputText("Name", secret.name);
    hpta_imgui::InputText("needs spell id", secret.needs_spell_id);
    hpta_imgui::InputText("needs item id", secret.needs_item_id);
    hpta_imgui::InputText("needs password", secret.needs_password);
    hpta_imgui::InputText("reveals item id", secret.reveals_item_id);
    hpta_imgui::InputTextMultilineWrapped("Description before reveal", secret.description_before_reveal);
    hpta_imgui::InputTextMultilineWrapped("Description after reveal", secret.description_after_reveal);
    hpta_imgui::InputTextMultilineWrapped("Text on reveal", secret.text_on_reveal);
    ImGui::PopItemWidth();
    ImGui::PopID();
}

} // namespace

std::vector<Room> Panel_Rooms::get_objects() { return m_room_cache.get_list(); }

void Panel_Rooms::refresh_cache() { m_room_cache.refresh(); }

void Panel_Rooms::create_object()
{
    m_current_object = Room{"/rooms/unknown.json"};

    m_current_object.set_name("no name");
    m_current_object.set_description("no description");
}

void Panel_Rooms::load_object()
{
    g_room.id          = m_current_object.get_id();
    g_room.name        = m_current_object.get_name();
    g_room.description = utils::wrap_text(m_current_object.get_description());

    g_exits.clear();
    for (const auto &exit : m_current_object.get_exits()) {
        UI_exit ui_exit;

        ui_exit.direction   = exit.direction;
        ui_exit.description = exit.description;
        ui_exit.room_id     = exit.room_id;

        g_exits.emplace_back(ui_exit);
    }

    g_secrets.clear();
    for (const auto &secret : m_current_object.get_secrets()) {
        UI_secret ui_secret;

        ui_secret.name                      = secret.name;
        ui_secret.description_before_reveal = secret.description_before_reveal;
        ui_secret.description_after_reveal  = secret.description_after_reveal;
        ui_secret.text_on_reveal            = secret.text_on_reveal;
        ui_secret.needs_spell_id            = secret.needs_spell_id;
        ui_secret.needs_item_id             = secret.needs_item_id;
        ui_secret.needs_password            = secret.needs_password;
        ui_secret.reveals_item_id           = secret.reveals_item_id;

        g_secrets.emplace_back(ui_secret);
    }
}

void Panel_Rooms::save_object()
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

    std::vector<Room::Secret> secrets;
    for (const auto &ui_secret : g_secrets) {
        Room::Secret secret;

        secret.name                      = ui_secret.name;
        secret.description_before_reveal = ui_secret.description_before_reveal;
        secret.description_after_reveal  = ui_secret.description_after_reveal;
        secret.text_on_reveal            = ui_secret.text_on_reveal;
        secret.needs_spell_id            = ui_secret.needs_spell_id;
        secret.needs_item_id             = ui_secret.needs_item_id;
        secret.needs_password            = ui_secret.needs_password;
        secret.reveals_item_id           = ui_secret.reveals_item_id;

        secrets.emplace_back(secret);
    }
    m_current_object.set_secrets(secrets);

    persistency::save_room(Hpta_config::get_string(Settings::gamedata_dir), m_current_object);

    m_event_engine.publish(Event{Event::Type::ROOM_CHANGED, m_current_object.get_id(), ""});
}

void Panel_Rooms::show_attributes()
{
    ImGui::PushItemWidth(hpta_imgui::get_textwrapwidth());

    hpta_imgui::InputText("ID", g_room.id);
    hpta_imgui::InputText("Name", g_room.name);
    hpta_imgui::InputTextMultilineWrapped("Description", g_room.description);
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

void Panel_Rooms::show_tab_room_exits()
{

    ImGui::BeginTable("Directions", 4, ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders);

    ImGui::TableSetupColumn("Action##directions");
    ImGui::TableSetupColumn("Direction##directions");
    ImGui::TableSetupColumn("Description##directions");
    ImGui::TableSetupColumn("Room##directions");

    ImGui::TableHeadersRow();

    int i = 0;
    for (auto itr = g_exits.begin(); itr != g_exits.end(); ++itr) {
        ImGui::PushID(itr->direction.c_str());

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
            hpta_imgui::InputText("##direction", itr->direction);
            ImGui::PopItemWidth();

            ImGui::TableNextColumn();
            ImGui::PushItemWidth(-1);
            hpta_imgui::InputText("##description", itr->description);
            ImGui::PopItemWidth();

            ImGui::TableNextColumn();
            ImGui::PushItemWidth(-1);
            hpta_imgui::InputText("##room_id", itr->room_id);
            ImGui::PopItemWidth();

            if (ImGui::BeginDragDropTarget()) {
                ImGuiDragDropFlags target_flags = 0;

                target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("ROOM_ID", target_flags)) {
                    itr->room_id = static_cast<const char *>(payload->Data);
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

void Panel_Rooms::show_tab_room_secrets()
{
    ImGui::BeginTable("Secrets", 6, ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders);

    ImGui::TableSetupColumn("Action##secrets");
    ImGui::TableSetupColumn("Name##secrets");
    ImGui::TableSetupColumn("Needs item##secrets");
    ImGui::TableSetupColumn("Needs password##secrets");
    ImGui::TableSetupColumn("Needs spell##secrets");
    ImGui::TableSetupColumn("Reveals item##secrets");
    ImGui::TableHeadersRow();

    int i = 0;
    for (auto &ui_secret : g_secrets) {

        const auto imgui_id = fmt::format("secret{}", i++);

        ImGui::PushID(imgui_id.c_str());
        ImGui::TableNextRow();

        ImGui::TableNextColumn();
        if (ImGui::Button("Edit"))
            ImGui::OpenPopup(imgui_id.c_str());

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal(imgui_id.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            if (ImGui::Button("Close")) {
                ImGui::CloseCurrentPopup();
            }
            show_popup_edit_secret(ui_secret);

            ImGui::EndPopup();
        }

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.name.c_str());

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.needs_item_id.c_str());

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.needs_password.c_str());

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.needs_spell_id.c_str());

        ImGui::TableNextColumn();
        ImGui::TextUnformatted(ui_secret.reveals_item_id.c_str());

        ImGui::PopID();
    }

    ImGui::EndTable();

    if (ImGui::Button("Add Secret")) {
        UI_secret new_secret;

        new_secret.name                      = "unamed secret";
        new_secret.description_before_reveal = "<undefined>";
        new_secret.description_after_reveal  = "<undefined>";
        new_secret.text_on_reveal            = "<undefined>";
        g_secrets.emplace_back(new_secret);
    }
}

void Panel_Rooms::on_event(Event event)
{
    switch (event.event_type) {
    case Event::Type::ROOM_SELECTED: {

        auto objects = get_objects();

        for (int i = 0; i < static_cast<int>(objects.size()); i++) {

            const auto object = objects.at(static_cast<size_t>(i));

            if (object.get_id() == event.room_id) {
                m_current_index  = i;
                m_current_object = object;
                load_object();
            }
        }

        break;
    }
    default:
        break;
    }
}