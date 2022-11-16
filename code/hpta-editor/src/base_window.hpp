#ifndef BASE_WINDOW_HPP
#define BASE_WINDOW_HPP

#include "ipanel.hpp"
#include "object_cache.hpp"

#include <imgui.h>

template <typename Tobject>
class Base_Window : public IPanel {
  protected:
    const std::string m_name{};
    int               m_current_index{-1};
    Tobject m_current_object{""};

  public:
    explicit Base_Window(const std::string &name) : m_name{name} {}

    virtual void                 create_object()                    = 0;
    virtual void                 load_object(const Tobject &object) = 0;
    virtual std::vector<Tobject> get_objects()                      = 0;
    virtual void                 refresh_cache()                    = 0;
    virtual void                 save_object()                      = 0;
    virtual void                 show_attributes()                  = 0;

    void show_list()
    {
        auto objects = get_objects();

        for (int i = 0; i < static_cast<int>(objects.size()); i++) {

            const auto object = objects.at(static_cast<size_t>(i));

            if (ImGui::Selectable(object.get_id().c_str(), m_current_index == i)) {
                m_current_index  = i;
                m_current_object = object;
                load_object(object);
            }
        }
    }

    void refresh() override
    {
        ImGui::Begin(m_name.c_str());
        ImGui::SetWindowFontScale(Hpta_config::get_float(Settings::scale_factor));

        if (ImGui::Button("Refresh")) {
            refresh_cache();
            // m_event_engine.publish({Event::Type::ROOM_CHANGED});
        }

        ImGui::SameLine();
        if (ImGui::Button("Add")) {
            create_object();
        }

        ImGui::SameLine();
        if (ImGui::Button("Save")) {
            save_object();
        }

        ImGui::Separator();

        ImGui::BeginTable("table", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders, ImVec2(0.0f, -1.0f), -1.0f);
        ImGui::TableNextColumn();
        ImGui::PushItemWidth(-1);
        show_list();
        ImGui::PopItemWidth();
        ImGui::TableNextColumn();
        show_attributes();
        ImGui::EndTable();

        ImGui::End();
    }
};

#endif /* BASE_WINDOW_HPP */
