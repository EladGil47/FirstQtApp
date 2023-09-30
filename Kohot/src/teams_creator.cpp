#include "teams_creator.hpp"
#include "players_sorter.hpp"

#include <iostream>

std::shared_ptr<std::vector<Team>> TeamsCreator::createTeams(std::vector<std::shared_ptr<Player>> players, const uint16_t teams_amount, const uint16_t players_in_team_amount)
{
	// Team* m_teams = new Team[teams_amount];
	std::shared_ptr<std::vector<Team>> m_teams = std::make_shared<std::vector<Team>>(teams_amount);

	PlayersSorter::sortBySortOption(players, PlayersSorter::SortOptions::RATE);

	int i = 0;
	bool directLeft = true;
	for (int player_index = 0;player_index < players_in_team_amount; player_index++)
	{
		if (directLeft)
		{
			for (uint16_t team_index = 0; team_index < teams_amount;team_index++)
			{
				(*m_teams)[team_index].getPlayersCollectionRef().addItem(players[i]);

				if (team_index == 2)
				{
					directLeft = false;
				}
				i++;
			}
		}
		else
		{
			for (int team_index = 2; team_index >= 0;team_index--)
			{
				(*m_teams)[team_index].getPlayersCollectionRef().addItem(players[i]);
				if (team_index == 0)
				{
					directLeft = true;
				}
				i++;
			}
		}
	}

	//displayTeams
	// for (uint16_t team_index = 0; team_index < teams_amount;team_index++)
	// {
	// 	std::cout << "Team " << team_index + 1 << " : " << std::endl;
	// 	(*m_teams)[team_index].displayTeam();
	// 	std::cout << std::endl;
	// }

	return m_teams;
}


