#include "group_menu.hpp"
#include "final_menu.hpp"
#include "user_interaction.hpp"

#include "teams_creator.hpp" 

GroupMenu::GroupMenu(std::shared_ptr<Group> group) :Menu()
{
	std::vector<std::string> options = { "Add Player","Delete Player","Create Teams" ,"Change Group Name" ,"Go Back", "Exit"};
	initializeOptions(options);
	initializeHeader("Menu : ");

	m_group = group;
}

void GroupMenu::moveToFinalMenu()
{
	FinalMenu final_menu;
	m_exit_menus = final_menu.handle();
	m_stay_in_menu = !m_exit_menus;
}

size_t GroupMenu::getPlayerIndexFromUser()
{
	Menu show_players_menu;
	std::vector<std::string> options = m_group->getPlayersCollectionRef().getPlayersNames();
	show_players_menu.initializeOptions(options);
	size_t index = static_cast<size_t> (show_players_menu.getChoiceFromUser() - 1);
	return index;
}

void GroupMenu::onDeletePlayer()
{
	size_t size = m_group->getNumOfPlayers();
	if (size > 0)
	{
		size_t player_index = 0;
		if (size > 1)
		{
			player_index = getPlayerIndexFromUser();
		}
		m_group->deletePlayer(player_index);
		size = m_group->getNumOfPlayers();
		for (size_t index = player_index;index < size; index++)
		{
			m_group->getPlayersCollectionRef().getItem(index)->setId(static_cast<uint16_t>(index));
		}
	}
}

std::vector<std::shared_ptr<Player>> GroupMenu::chooseComingPlayers(uint16_t coming_players_amount) {

	std::vector<std::shared_ptr<Player>> coming_players;

	PlayersCollection players = m_group->getPlayersCollectionRef();
	for (uint16_t chosen_count = 0;chosen_count < coming_players_amount; chosen_count++)
	{
		std::cout << "Creating Teams :) \n\nPlease choose a player from the players list\n";
		Menu show_players_menu;
		show_players_menu.initializeHeader("Players list : ");
		std::vector<std::string> options = players.getPlayersNames();
		show_players_menu.initializeOptions(options);
		size_t index = static_cast<size_t> (show_players_menu.getChoiceFromUser() - 1);
		coming_players.push_back(players.getItem(index));
		players.deleteItem(index);
	}
	return coming_players;
}

uint16_t GroupMenu::getTeamsAmountFromUser()
{
	const uint16_t MIN_TEAM_AMOUNT_CHOICE = 2;
	uint16_t teams_amount = m_group->getTeamsAmount();
	if (teams_amount == 0)
	{
		const uint16_t MAX_POSSIBLE_CHOICE = static_cast<uint16_t>(m_group->getNumOfPlayers()) / MIN_TEAM_AMOUNT_CHOICE;
		teams_amount = UserInteraction::getUint16FromUser("Amount of teams", MIN_TEAM_AMOUNT_CHOICE, MAX_POSSIBLE_CHOICE);
	}
	return teams_amount;
}

uint16_t GroupMenu::getPlayersInTeamAmountFromUser(uint16_t teams_amount)
{
	const uint16_t MIN_PLAYERS_IN_TEAM_AMOUNT = 2;
	uint16_t players_in_team_amount = m_group->getPlayersInTeamAmount();
	if (players_in_team_amount == 0)
	{
		const uint16_t MAX_POSSIBLE_CHOICE = static_cast<uint16_t>(m_group->getNumOfPlayers()) / teams_amount;
		teams_amount = UserInteraction::getUint16FromUser("Amount of players in a team", MIN_PLAYERS_IN_TEAM_AMOUNT, MAX_POSSIBLE_CHOICE);
	}
	return players_in_team_amount;
}

bool GroupMenu::handle()
{ 
	while (m_stay_in_menu && !m_exit_menus)
	{
		m_group->displayGroup();
		switch (getChoosenOption())
		{
		case GroupMenuOption::ADD_PLAYER:
		{
			m_group->addPlayer();
			break;
		}
		case GroupMenuOption::DELETE_PLAYER:
		{
			onDeletePlayer();
			break;
		}
		case GroupMenuOption::CREATE_TEAMS:
		{
			uint16_t teams_amount = getTeamsAmountFromUser();
			uint16_t players_in_team_amount = getPlayersInTeamAmountFromUser(teams_amount);
			const uint16_t COMING_PLAYERS_AMOUNT = teams_amount * players_in_team_amount;
			TeamsCreator::createTeams(chooseComingPlayers(COMING_PLAYERS_AMOUNT), teams_amount ,players_in_team_amount);

			moveToFinalMenu();
			break;
		}
		case GroupMenuOption::CHANGE_GROUP_NAME:
		{
			m_group->changeName();
			break;
		}
		case GroupMenuOption::GO_BACK:
		{
			m_stay_in_menu = false;
			break;
		}
		case GroupMenuOption::EXIT:
		{
			m_exit_menus = true;
			break;
		}
		default:
			break;
		}
		system("clear");
	}
	return m_exit_menus;
}
