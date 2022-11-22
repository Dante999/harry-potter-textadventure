#ifndef IPANEL_HPP
#define IPANEL_HPP

#include <string>

class IPanel {
  protected:
    const std::string m_name{};

  public:
    IPanel(const std::string &name) : m_name{name} {}

    virtual void refresh() = 0;

    virtual ~IPanel() = default;

    [[nodiscard]] const auto get_name() const { return m_name; }
};

#endif // IPANEL_HPP
