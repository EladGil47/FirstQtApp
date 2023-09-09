#include "players_collection.hpp"
#include "players_sorter.hpp"

#include <iomanip>
#include <iostream>

#include "console_colors.hpp"


Player::Config PlayersCollection::getPlayerConfigFromUser()
{
	std::cout << "Creating a new player... \n\n";

	std::string name;
	std::cout << "Please enter name :  ";
	std::cin >> name;

	double rate;
	std::cout << "Please enter rate :  ";
	std::cin >> rate;

	uint16_t role_choose;
	std::cout << "Please enter role : \n 0 - GK \n 1 - Baller" << std::endl;
	std::cin >> role_choose;
	Player::Role role = static_cast<Player::Role>(role_choose);
	Player::Config player_config = { static_cast<uint16_t>( getSize()),name,rate,role };
	return player_config;
}

void PlayersCollection::createItem()
{
	std::shared_ptr<Player> new_player = std::make_shared<Player>(getPlayerConfigFromUser());
	addItem(new_player);
}

void PlayersCollection::display()
{
	PlayersSorter::sortBySortOption(getCollectionRef(), PlayersSorter::SortOptions::NAME);

	std::cout << GREEN << std::left << "Players:" << std::endl;

	if (!m_collection.empty())
	{
		std::cout  <<  YELLOW << std::left
			<< std::setw(5) << "#"
			<< std::setw(20) << "Name"
			<< std::setw(10) << "Rate"
			<< std::setw(10) << "Role"
			<< RESET
			<< std::endl;

		
		uint16_t iteration_number = 1;
		for (std::shared_ptr <Player> p : m_collection)
		{
			std::cout << RED << std::left
				<< std::setw(5) << iteration_number
				<< std::setw(20) << p->getName()
				<< std::fixed << std::setprecision(2) << std::setw(10) << p->getRate()
				<< std::setw(10) << p->getRoleText()
				<< RESET
				<< std::endl;

				iteration_number++;
		}
	}
	else
	{
		std::cout  << "There is no players";
	}
}