#include "final_menu.hpp"

FinalMenu::FinalMenu() : Menu()
{
	std::vector<std::string> options = {GO_BACK, EXIT };
	initializeOptions(options);
}

bool FinalMenu::handle()
{
	while (m_stay_in_menu)
	{
		switch (getChoosenOption())
		{
		case FinalMenuOption::GO_BACK:
		{
			m_stay_in_menu = false;
			break;
		}
		case FinalMenuOption::EXIT:
		{
			m_exit_menus = true;
			m_stay_in_menu = false;
			break;
		}
		default:
			break;
		}
		system("clear");
	}
	return m_exit_menus;
}
