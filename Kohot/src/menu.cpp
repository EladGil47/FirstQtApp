#include "menu.hpp"
#include <iostream>

#include "user_interaction.hpp"


void Menu::displayMenu()
{
	std::cout << std::endl << m_header << std::endl;
	for (size_t option_index = 0; option_index < m_options.size(); option_index++)
	{
		std::cout << (option_index + 1) << ". " << m_options[option_index] << std::endl;
	}
}

bool Menu::handle()
{
	return true;
}

void Menu::initializeOptions(std::vector<std::string> options)
{
	m_options = options;
}


void Menu::initializeHeader(std::string header)
{
	m_header = header;
}


uint16_t Menu::getChoiceFromUser()
{
	displayMenu();

	uint16_t ret_val = UserInteraction::getUint16FromUser("your choice", 1, static_cast<uint16_t>( m_options.size()));
	system("cls");

	return ret_val;
}
