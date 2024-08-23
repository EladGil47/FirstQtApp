#include "static_settings.hpp"

// Initialize static members
std::vector<int32_t> StaticSettings::players_in_team_range;
std::vector<int32_t> StaticSettings::team_range;

void StaticSettings::init(std::shared_ptr<Settings> settings)
{
    players_in_team_range = settings->getPlayersInTeamRange();
    team_range            = settings->getTeamRange();
}
