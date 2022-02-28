#ifndef JSON_FILEHANDLER_HPP
#define JSON_FILEHANDLER_HPP

#include <functional>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>

namespace Json_filehandler {

inline void load(const std::string &gamedata_dir, const std::string &id,
                 std::function<void(rapidjson::Document &)> consumer)
{
	const std::string filepath(gamedata_dir + id);

	FILE *fp = fopen(filepath.c_str(), "rb"); // non-Windows use "r"

	if (fp == NULL) {
		throw std::runtime_error("Can not find file " + filepath);
	}

	char readBuffer[65536];

	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document d;
	d.ParseStream(is);

	fclose(fp);

	consumer(d);
}

inline void save(const std::string &gamedata_dir, const std::string &id,
                 std::function<void(rapidjson::PrettyWriter<rapidjson::FileWriteStream> &)> consumer)
{
	const std::string filepath(gamedata_dir + id);

	FILE *fp = fopen(filepath.c_str(), "wb"); // non-Windows use "r"

	if (fp == NULL) {
		throw std::runtime_error("Can open file " + filepath);
	}

	char writeBuffer[65536];

	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	consumer(writer);

	fclose(fp);
}

} // namespace Json_filehandler
#endif // JSON_FILEHANDLER_HPP
