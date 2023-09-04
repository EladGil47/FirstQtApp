#ifndef KOHOT_JSON_UTILS_HPP
#define KOHOT_JSON_UTILS_HPP

#include "nlohmann/json.hpp"

class JsonUtils
{
public: 
	static void serializeJson(const nlohmann::json& data, const char* path);
	static void deserializeToJson(const char* path, nlohmann::json& data);
};

#endif //KOHOT_JSON_UTILS_HPP

