#ifndef HPTA_CONFIG_HPP
#define HPTA_CONFIG_HPP

#include "hpta-lib/util/hpta_strings.hpp"

#include <istream>
#include <map>
#include <string>

class Hpta_config {
  private:
	static std::map<std::string, std::string> m_values;

  public:
	static void load(std::istream &is);

	template <typename T>
	static void add(const std::string &key, const T &value)
	{
		m_values[Hpta_strings::trim(key)] = Hpta_strings::trim(std::to_string(value));
	}


	static void add(const std::string &key, const std::string &value)
	{
		m_values[Hpta_strings::trim(key)] = Hpta_strings::trim(value);
	}

	static std::string &get_string(const std::string &key);
	static float get_float(const std::string &key);
	static int get_int(const std::string &key);
	static unsigned int get_uint(const std::string &key);
};

#endif // HPTA_CONFIG_HPP
