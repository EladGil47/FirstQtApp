#ifndef KOHOT_TEAM_HPP
#define KOHOT_TEAM_HPP

#include "players_collection.hpp"

class Team 
{
public:
	Team();
	PlayersCollection& getPlayersCollectionRef();
	void displayTeam();
private :
	PlayersCollection m_players_collection;

};

#endif //KOHOT_TEAM_HPP