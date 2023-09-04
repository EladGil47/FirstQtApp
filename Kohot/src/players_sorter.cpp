#include "players_sorter.hpp"

#include <algorithm>


bool PlayersSorter::compareByRate(std::shared_ptr<Player> a, std::shared_ptr<Player> b)
{
	return a->getRate() > b->getRate();
}
bool PlayersSorter::compareByName(std::shared_ptr<Player> a, std::shared_ptr<Player> b) 
{
	return a->getName() < b->getName();
}
uint16_t PlayersSorter::countGoalKeepers(std::vector<std::shared_ptr<Player>> players)
{
	uint16_t amount_of_goal_keepers = 0; 
	for (std::shared_ptr<Player> p : players)
	{
		if (p->getRole() == Player::Role::GK)
		{
			amount_of_goal_keepers++;
		}
		else
		{
			break;
		}
	}
	return amount_of_goal_keepers;
}


void  PlayersSorter::sortBySortOption(std::vector<std::shared_ptr<Player>> &players, SortOptions sort_option)
{
	uint16_t amount_of_goal_keepers = countGoalKeepers(players);
	switch (sort_option)
	{
	case SortOptions::RATE:
	{
		//Sort Keepers
		std::sort(players.begin(), players.begin() + amount_of_goal_keepers, compareByRate);
		//Sort Ballers
		std::sort(players.begin() + amount_of_goal_keepers, players.end(), compareByRate);
		break;
	}
	case SortOptions::NAME:
	{
		//Sort Keepers
		std::sort(players.begin(), players.begin() + amount_of_goal_keepers, compareByName);
		//Sort Ballers
		std::sort(players.begin() + amount_of_goal_keepers, players.end(), compareByName);
		break;
	}
	}

	/*int index = 0;
	for (std::shared_ptr<Player> p : players)
	{
		p->setId(index);
		index++;
	}*/
}

//void  PlayersSorter::sortBySortOption(std::shared_ptr<std::vector<std::shared_ptr<Player>>> players, SortOptions sort_option)
//{
//	uint16_t amount_of_goal_keepers = countGoalKeepers(*players);
//	switch (sort_option)
//	{
//	case SortOptions::RATE:
//	{
//		//Sort Keepers
//		std::sort(players->begin(), players->begin() + amount_of_goal_keepers, compareByRate);
//		//Sort Ballers
//		std::sort(players->begin() + amount_of_goal_keepers, players->end(), compareByRate);
//		break;
//	}
//	case SortOptions::NAME:
//	{
//		//Sort Keepers
//		std::sort(players->begin(), players->begin() + amount_of_goal_keepers, compareByName);
//		//Sort Ballers
//		std::sort(players->begin() + amount_of_goal_keepers, players->end(), compareByName);
//		break;
//	}
//	}
//
//	/*int index = 0;
//	for (std::shared_ptr<Player> p : players)
//	{
//		p->setId(index);
//		index++;
//	}*/
//}
