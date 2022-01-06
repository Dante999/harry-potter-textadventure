#include "hpta-lib/util/hpta_config.hpp"

#include "hpta-lib/util/hpta_strings.hpp"

std::map<std::string, std::string> Hpta_config::m_values;

void Hpta_config::load(std::istream &is)
{
	std::string line;

	int line_number = 1;

	while (getline(is, line)) {

		if (line.empty() || Hpta_strings::ltrim(line).at(0) == '#') {
			continue;
		}

		const auto delimiter = line.find('=');

		if (delimiter == std::string::npos) {
			throw std::runtime_error("no '=' delimiter found for line " + std::to_string(line_number));
		}

		const auto key   = Hpta_strings::trim(line.substr(0, delimiter));
		const auto value = Hpta_strings::trim(line.substr(delimiter + 1));

		m_values.insert(std::make_pair(key, value));
	}
}

std::string &Hpta_config::get_string(const std::string &key)
{
	if (const auto &val = m_values.find(key); val != m_values.end()) {
		return val->second;
	}

	throw std::runtime_error("no value for key '" + key + "' found!");
}

float Hpta_config::get_float(const std::string &key)
{
	return std::stof(get_string(key));
}

int Hpta_config::get_int(const std::string &key)
{
	return std::stoi(get_string(key));
}

unsigned int Hpta_config::get_uint(const std::string &key)
{
	return static_cast<unsigned int>(std::stoul(get_string(key)));
}
