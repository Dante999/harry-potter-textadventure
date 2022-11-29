#ifndef WINDOW_BASE_HPP
#define WINDOW_BASE_HPP

#include "ipanel.hpp"
#include "object_cache.hpp"

#include <imgui.h>

template <typename Tobject>
class Panel_Base : public IPanel {
  protected:
    int     m_current_index{-1};
    Tobject m_current_object{""};
    World_Cache& m_world_cache;

  public:
    explicit Panel_Base(const std::string &name, World_Cache& world_cache) : IPanel{name}, m_world_cache{world_cache} {}

    virtual void                 create_object()   = 0;
    virtual void                 load_object()     = 0;
    virtual std::vector<Tobject> get_objects()     = 0;
    virtual void                 refresh_cache()   = 0;
    virtual void                 save_object()     = 0;
    virtual void                 show_attributes() = 0;

    void show_list()
    {
        auto objects = get_objects();

        for (int i = 0; i < static_cast<int>(objects.size()); i++) {

            const auto object = objects.at(static_cast<size_t>(i));

            if (ImGui::Selectable(object.get_id().c_str(), m_current_index == i)) {
                m_current_index  = i;
                m_current_object = object;
                load_object();
            }
        }
    }

    void refresh() override
    {
        ImGui::PushID(m_name.c_str());

        if (ImGui::Button("Refresh")) {
            refresh_cache();
            // m_event_engine.publish({Event::Type::ROOM_CHANGED});
        }

        ImGui::SameLine();
        if (ImGui::Button("Add")) {
            m_current_index = -1;
            create_object();
            load_object();
        }

        ImGui::SameLine();
        if (ImGui::Button("Save")) {
            save_object();
            refresh_cache();
        }

        ImGui::Separator();

        ImGui::BeginTable("table", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders, ImVec2(0.0f, 0.0f), 0.0f);
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        show_list();

        ImGui::TableSetColumnIndex(1);
        show_attributes();

        ImGui::EndTable();

        ImGui::PopID();
    }
};

#endif /* WINDOW_BASE_HPP */
