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

Team::Team() {
	m_players_collection = std::make_shared<PlayersCollection>();
}

void Team::displayTeam()
{
	size_t num_of_players_in_team =  m_players_collection->getSize();
	for (std::uint16_t player_index = 0;player_index < num_of_players_in_team; player_index++)
	{
		std::shared_ptr<Player> player = m_players_collection->getItem(player_index);
		std::cout << player->getName() << std::endl;
		m_rating_sum += player ->getRate();
	}
	double rating_average = m_rating_sum / num_of_players_in_team;
	std::cout <<"Rating average : " << rating_average  << std::endl;
}