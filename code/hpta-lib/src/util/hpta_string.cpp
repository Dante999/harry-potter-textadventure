#include "util/hpta_strings.hpp"

#include <algorithm>
#include <sstream>

namespace Hpta_strings {

const std::vector<std::string> split_text_into_lines(const std::string &text, size_t column_width)
{
	std::vector<std::string> lines;

	if (text.length() < column_width) {
		lines.emplace_back(text);
		return lines;
	}

	size_t idx_line = 0;
	size_t idx_old  = 0;
	size_t idx_new  = text.find(' ', idx_line);

	while (idx_new != std::string::npos) {
		if (idx_new - idx_line < column_width) {
			idx_old = idx_new;
		}
		else {
			lines.emplace_back(text.substr(idx_line, idx_old - idx_line));
			idx_line = idx_old + 1;
		}

		idx_new = text.find(' ', idx_new + 1);

		if (idx_new == std::string::npos) {
			lines.emplace_back(text.substr(idx_line, text.length() - idx_line));
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

} // namespace Hpta_strings
