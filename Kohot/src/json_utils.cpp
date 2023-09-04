#include "json_utils.hpp"

#include <fstream>
#include <iostream>

void JsonUtils::serializeJson(const nlohmann::json &data, const char* path)
{
	std::ofstream groups_outfile(path, std::ofstream::out);
	if (groups_outfile.is_open())
	{
		groups_outfile << data;
	}
	else {
		std::cout << "Failed To open " << path;
	}
	groups_outfile.close();
}

void JsonUtils::deserializeToJson(const char* path, nlohmann::json & data)
{
	std::ifstream groups_infile(path);
	if (groups_infile.is_open())
	{
		groups_infile >> data;
	}
	else {
		std::cout << "Failed To open " << path;
	}
	groups_infile.close();
}