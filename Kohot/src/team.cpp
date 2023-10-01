#include "team.hpp"

#include <iostream>

// PlayersCollection& Team::getPlayersCollectionRef()
// {
// 	return m_players_collection;
// }

// PlayersCollection Team::getPlayersCollection()
// {
// 	return m_players_collection;
// }

Team::Team() {
	m_players_collection = std::make_shared<PlayersCollection>();
}

std::shared_ptr<PlayersCollection> Team::getPlayersCollection()
{
	return m_players_collection;
}

void Team::addPlayer(std::shared_ptr<Player> player)
{
	if (m_players_collection)
	{
		m_players_collection->addItem(player);
	}
}



void Team::displayTeam()
{
	double rating_sum = 0;
	size_t num_of_players_in_team =  m_players_collection->getSize();
	for (std::uint16_t player_index = 0;player_index < num_of_players_in_team; player_index++)
	{
		std::shared_ptr<Player> player = m_players_collection->getItem(player_index);
		std::cout << player->getName() << std::endl;
		rating_sum += player ->getRate();
	}
	double average_rate = rating_sum / num_of_players_in_team;
	std::cout <<"Avarage Rate : " << average_rate  << std::endl;
}

double Team::getAverageRate()
{
	double rating_sum = 0;
	size_t num_of_players_in_team = m_players_collection->getSize();
	for (std::uint16_t player_index = 0; player_index < num_of_players_in_team; player_index++)
	{
		std::shared_ptr<Player> player = m_players_collection->getItem(player_index);
		rating_sum += player->getRate();
	}
	double average_rate = rating_sum / num_of_players_in_team;
	return average_rate;
}