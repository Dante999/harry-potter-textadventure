#ifndef HPTA_STRINGS_HPP
#define HPTA_STRINGS_HPP

#include <string>
#include <vector>

namespace Hpta_strings {

[[nodiscard]] const std::vector<std::string> split_text_into_lines(const std::string &text, size_t column_width);

[[nodiscard]] const std::string add_newline_on_column_width(const std::string &text, size_t column_width);
[[nodiscard]] const std::string remove_newlines(const std::string &text);

[[nodiscard]] bool equals_ignorecase(const std::string &s1, const std::string &s2);

} // namespace Hpta_strings

#endif // HPTA_STRINGS_HPP
