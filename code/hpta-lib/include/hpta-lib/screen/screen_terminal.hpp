#ifndef SCREEN_H
#define SCREEN_H

#include "hpta-lib/screen/iscreen.hpp"

class Screen_Terminal : public IScreen {
    void hline() override;
    void print(const std::string &msg) override;
    void println(const std::string &msg) override;
    void print_wrapped(const std::string &msg) override;
    void box_start(const std::string &caption) override;
    void box_end() override;

    const std::string ask_for(const std::string &msg) override;
    const std::string highlight(const std::string &msg) override;
};

#endif /* SCREEN_H */
