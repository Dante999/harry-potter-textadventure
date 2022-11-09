#ifndef USER_INTERACTION_SERVICE_HPP
#define USER_INTERACTION_SERVICE_HPP

#include "hpta-lib/screen/iscreen.hpp"
#include "hpta-lib/visualizer.hpp"

#include <memory>

class User_Interaction_Service {
  private:
    const std::shared_ptr<IScreen>    m_screen;
    const std::shared_ptr<Visualizer> m_visualizer;

  public:
    explicit User_Interaction_Service(std::shared_ptr<IScreen> screen)
        : m_screen{screen}, m_visualizer{std::make_shared<Visualizer>(m_screen)} {};

    const auto get_screen() const
    {
        return m_screen;
    }

    const auto get_visualizer() const
    {
        return m_visualizer;
    }
};

#endif /* USER_INTERACTION_SERVICE_HPP */
