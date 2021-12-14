#ifndef SCREEN_H
#define SCREEN_H

#include <string>

namespace Screen {
constexpr uint8_t column_width = 80;

void hline();
void print(const std::string &msg);
void box_start(const std::string &caption);
void box_end();

const std::string ask_for(const std::string &msg);
} // namespace Screen

#endif /* SCREEN_H */
