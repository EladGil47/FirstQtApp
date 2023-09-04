#include "kohot.hpp"

#include "groups_manager_menu.hpp"
#include "json_utils.hpp"

#include <iostream>

std::shared_ptr<GroupsCollection> Kohot::getGroupsCollection()
{
	return m_groups_collection;
}

void Kohot::loadGroups()
{
	nlohmann::json groups_data;
	JsonUtils::deserializeToJson(GROUPS_FILE_PATH, groups_data);

	for (const auto& group : groups_data["Groups"]) {
			const Group::Config group_config = {
				static_cast<uint16_t>(m_groups_collection->getSize()),
				group["Name"].get<std::string>(),
					 3,
					 5
			};
			std::shared_ptr<Group> group_ptr = std::make_shared <Group>(group_config);

			uint16_t player_id = 0;
			for (const auto& player : group["Players"])
			{
				const Player::Config player_config = {
				player_id++,
				player["Name"].get<std::string>(),
				player["Rate"].get<double>(),
				Player::toPlayerRole( player["Role"].get<std::string>())
				};
				std::shared_ptr<Player> additional_player = std::make_shared<Player>(player_config);
				group_ptr->getPlayersCollectionRef().addItem(additional_player);
			}
			m_groups_collection->addItem(group_ptr);
		}
}

void Kohot::saveGroups() {
	nlohmann::json data;

	nlohmann::json& groups_array = data["Groups"];
	groups_array = nlohmann::json::array();

	uint16_t group_index = 0;
	for (std::shared_ptr<Group> group : m_groups_collection->getCollection())
	{
		nlohmann::json& json_group = groups_array[group_index];

		json_group["Id"] = group->getId();
		json_group["Name"] = group->getName();
		nlohmann::json& players_array = json_group["Players"];
		players_array = nlohmann::json::array();
			
		uint16_t player_index = 0;
		for (std::shared_ptr<Player> player : group->getPlayersCollectionRef().getCollection())
		{
			nlohmann::json& json_player = players_array[player_index];

			json_player["Id"] = player->getId();
			json_player["Name"] = player->getName();
			json_player["Rate"] = player->getRate();
			json_player["Role"] = player->getRoleText();

			player_index++;
		}
		group_index++; 
	}

	JsonUtils::serializeJson(data, GROUPS_FILE_PATH);
}

