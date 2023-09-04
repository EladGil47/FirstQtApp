#include "team.hpp"

#include <iostream>

PlayersCollection& Team::getPlayersCollectionRef()
{
	return m_players_collection;
}

Team::Team() {}

void Team::displayTeam()
{
	double rating_sum = 0;
	size_t num_of_players_in_team =  m_players_collection.getSize();
	for (std::uint16_t player_index = 0;player_index < num_of_players_in_team; player_index++)
	{
		std::shared_ptr<Player> player = m_players_collection.getItem(player_index);
		std::cout << player->getName() << std::endl;
		rating_sum += player ->getRate();
	}
	double rating_average = rating_sum / num_of_players_in_team;
	std::cout <<"Rating average : " << rating_average  << std::endl;
}