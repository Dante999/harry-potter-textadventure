#ifndef HPTA_STRINGS_HPP
#define HPTA_STRINGS_HPP

#include <string>
#include <vector>

namespace Hpta_strings {

[[nodiscard]] const std::vector<std::string> split_text_into_lines(const std::string &text, size_t column_width);

[[nodiscard]] const std::string add_newline_on_column_width(const std::string &text, size_t column_width);
[[nodiscard]] const std::string remove_newlines(const std::string &text);

[[nodiscard]] bool equals_ignorecase(const std::string &s1, const std::string &s2);
[[nodiscard]] bool equals_one_of(const std::string &s, const std::vector<std::string> &s_list);

[[nodiscard]] std::string ltrim(const std::string &s);
[[nodiscard]] std::string rtrim(const std::string &s);
[[nodiscard]] std::string trim(const std::string &s);

[[nodiscard]] bool ends_with(const std::string &s, const std::string &end);

} // namespace Hpta_strings

#endif // HPTA_STRINGS_HPP
