#ifndef KOHOT_GROUP_HPP
#define KOHOT_GROUP_HPP

#include "players_collection.hpp"


class Group
{
public:
	struct Config
	{
		uint16_t id;
		std::string name;
		uint16_t teams_amount = 0; 
		uint16_t players_in_team_amount = 0;
	};

	Group(const Group::Config &config);
	Group& operator=(const Group& other_group);

	PlayersCollection& getPlayersCollectionRef();
	PlayersCollection getPlayersCollection();

	uint16_t getTeamsAmount();
	uint16_t getPlayersInTeamAmount();
	void setId(uint16_t id);


	Group::Config getConfig();
	std::string getName( );
	uint16_t getId();

	void setConfig(const Group::Config& config);
	void setPlayersCollection(PlayersCollection players_collection);
	void setName(std::string name);

	void changeName();

	//void createTeams(uint16_t teams_amount, uint16_t players_in_team_amount);
	void displayGroup();

	void addPlayer();
	void deletePlayer(size_t index );
	size_t getNumOfPlayers();

private:
	Group::Config m_config;
	PlayersCollection m_players_collection;

	//std::vector<std::shared_ptr<Player>> chooseComingPlayers(uint16_t coming_players_amount);
};

#endif // KOHOT_GROUP_HPP

