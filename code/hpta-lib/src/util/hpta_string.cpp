#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <sstream>

[[nodiscard]] bool Hpta_strings::equals_one_of(const std::string &s, const std::vector<std::string> &s_list)
{
    return std::any_of(std::begin(s_list), std::end(s_list), [&s](const auto &rhs) { return s == rhs; });
}

namespace Hpta_strings {

const std::string WHITESPACE = " \n\r\t\f\v";

const std::vector<std::string> split_text_into_lines(const std::string &text, size_t column_width)
{

    std::vector<std::string> lines;

    if (text.length() < column_width) {
        lines.emplace_back(text);
        return lines;
    }

    size_t idx_linestart = 0;
    size_t idx_spaceold  = 0;
    size_t idx_spacenew  = text.find(' ', idx_linestart);

    while (idx_spacenew != std::string::npos) {

        // TODO: Ignore nonprintable characters

        if (idx_spacenew - idx_linestart < column_width) {
            idx_spaceold = idx_spacenew;
        }
        else {
            lines.emplace_back(text.substr(idx_linestart, idx_spaceold - idx_linestart));
            idx_linestart = idx_spaceold + 1;
        }

        idx_spacenew = text.find(' ', idx_spacenew + 1);

        if (idx_spacenew == std::string::npos) {
            lines.emplace_back(text.substr(idx_linestart, text.length() - idx_linestart));
        }
    }

    return lines;
}

const std::string add_newline_on_column_width(const std::string &text, size_t column_width)
{
    const auto lines = split_text_into_lines(text, column_width);

    std::stringstream ss;

    for (const auto &line : lines) {
        ss << line << '\n';
    }

    return ss.str();
}

[[nodiscard]] const std::string remove_newlines(const std::string &text)
{
    auto result = text;

    std::replace(result.begin(), result.end(), '\n', ' ');

    size_t idx = result.find("  ", 0);

    while (idx != std::string::npos) {
        result.erase(idx, 1);

        idx = result.find("  ", idx + 1);
    }

    return result;
}

bool equals_ignorecase(const std::string &s1, const std::string &s2)
{
    std::string s1_lower{s1};
    std::string s2_lower{s2};

    transform(s1_lower.begin(), s1_lower.end(), s1_lower.begin(), ::tolower);
    transform(s2_lower.begin(), s2_lower.end(), s2_lower.begin(), ::tolower);

    return s1_lower == s2_lower;
}

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) { return rtrim(ltrim(s)); }

bool ends_with(const std::string &s, const std::string &end) { return (s.substr(s.length() - end.length()) == end); }

[[nodiscard]] const std::vector<std::string> get_highlighted_text(const std::string &text, char marker_start, char marker_end)
{
    std::vector<std::string> result;

    size_t idx_start = text.find(marker_start, 0);
    size_t idx_end   = text.find(marker_end, idx_start+1);

    while( idx_start != std::string::npos && idx_end != std::string::npos)
    {
        result.emplace_back(text.substr(idx_start, idx_end-idx_start+1));

        idx_start = text.find(marker_start, idx_end+1);
        idx_end   = text.find(marker_end, idx_start+1);
    }
    
    return result;
}

void replace(std::string &text, const std::string &old_word, const std::string &new_word)
{

    while (text.find(old_word) != std::string::npos) {
        text.replace(text.find(old_word), old_word.length(), new_word);
    }

}

} // namespace Hpta_strings
