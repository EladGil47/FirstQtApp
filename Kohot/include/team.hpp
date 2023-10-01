#ifndef KOHOT_TEAM_HPP
#define KOHOT_TEAM_HPP

#include "players_collection.hpp"

class Team 
{
public:
	Team();
	// PlayersCollection& getPlayersCollectionRef();
	// PlayersCollection getPlayersCollection();
	std::shared_ptr<PlayersCollection> getPlayersCollection();
	void addPlayer(std::shared_ptr<Player> player);
	double getAverageRate();

	void displayTeam();
private :
	std::shared_ptr<PlayersCollection> m_players_collection;
};

#endif //KOHOT_TEAM_HPP