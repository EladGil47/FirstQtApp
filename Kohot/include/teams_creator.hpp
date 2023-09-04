#ifndef KOHOT_TEAMS_CREATOR_HPP
#define KOHOT_TEAMS_CREATOR_HPP

#include <vector>
#include <memory>

#include "Player.hpp"

class TeamsCreator 
{
public:
	static void createTeams(std::vector<std::shared_ptr<Player>> players, const uint16_t teams_amount, const uint16_t players_in_team_amount);
};

#endif //KOHOT_TEAMS_CREATOR_HPP