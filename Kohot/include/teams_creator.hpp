#ifndef KOHOT_TEAMS_CREATOR_HPP
#define KOHOT_TEAMS_CREATOR_HPP

#include <vector>
#include <memory>

#include "player.hpp"
#include "team.hpp"


class TeamsCreator 
{
public:
	static std::shared_ptr<std::vector<Team>> createTeams(std::vector<std::shared_ptr<Player>> players, const uint16_t teams_amount, const uint16_t players_in_team_amount);
};

#endif //KOHOT_TEAMS_CREATOR_HPP
