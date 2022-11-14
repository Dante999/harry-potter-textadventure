#ifndef ISCREEN_HPP
#define ISCREEN_HPP

#include <cstddef>
#include <string>

class IScreen {

  public:
    virtual ~IScreen() = default;

    static constexpr uint8_t column_width = 80;
    static constexpr uint8_t tab_width    = 8;

    virtual void hline()                               = 0;
    virtual void print(const std::string &msg)         = 0;
    virtual void println(const std::string &msg)       = 0;
    virtual void box_start(const std::string &caption) = 0;
    virtual void box_end()                             = 0;

    virtual const std::string ask_for(const std::string &msg)   = 0;
    virtual const std::string highlight(const std::string &msg) = 0;
};

#endif /* ISCREEN_HPP */
