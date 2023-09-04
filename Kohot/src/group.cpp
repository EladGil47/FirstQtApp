#include "group.hpp"

//#include "teams_creator.hpp" 
//#include "players_sorter.hpp"
//#include <iomanip> 

#include <iostream>


Group::Group(const Group::Config& config)  
{
	setConfig(config);
}

Group& Group::operator=(const Group& other_group)
{
	if (this == &other_group)
		return *this; // Self-assignment check

	// Copy Config member (since it contains a const member, it cannot be directly assigned)
	setConfig(other_group.m_config);
	setPlayersCollection(other_group.m_players_collection);

	return *this;
}

uint16_t  Group::getPlayersInTeamAmount()
{
	return m_config.players_in_team_amount;
}

uint16_t Group::getTeamsAmount()
{
	return m_config.teams_amount;
}

void Group::addPlayer()
{
	m_players_collection.createItem();
}

void Group::deletePlayer(size_t index)
{
	m_players_collection.deleteItem(index);
}

size_t Group::getNumOfPlayers()
{
	return m_players_collection.getSize();
}

PlayersCollection& Group:: getPlayersCollectionRef()
{
	return m_players_collection;
}

PlayersCollection Group::getPlayersCollection()
{
	return m_players_collection;
}


void Group::changeName()
{
	std::string new_name;
	std::cout << "Please enter name :  ";
	std::cin >> new_name;
	setName(new_name);
}


void Group::setName(std::string name) {
	m_config.name = name;
}

void Group::setId(uint16_t id) {
	m_config.id = id;
}

std::string Group::getName() {
	return m_config.name;
}

uint16_t Group::getId()
{
	return m_config.id;
}

Group::Config Group::getConfig()
{
	return m_config;
}

void Group::displayGroup()
{
	std::cout << getName() << ":" << std::endl;
	m_players_collection.display();
}

void Group::setConfig(const Group::Config& config)
{
	m_config.id = config.id;
	m_config.name = config.name;
	m_config.teams_amount = config.teams_amount;
	m_config.players_in_team_amount = config.players_in_team_amount;
}

void Group::setPlayersCollection(PlayersCollection players_collection)
{
	m_players_collection = players_collection;
}
//std::vector<std::shared_ptr<Player>> Group::chooseComingPlayers(uint16_t coming_players_amount) {
//
//	std::vector<std::shared_ptr<Player>> coming_players;
//
//	PlayersCollection players = m_players_collection;
//	for (uint16_t chosen_count = 0;chosen_count < coming_players_amount; chosen_count++)
//	{
//		std::cout << "Creating Teams :) \nPlease choose a player from the menu  ";
//		Menu show_players_menu;
//		std::vector<std::string> options = players.getPlayersNames();
//		show_players_menu.initializeOptions(options);
//		size_t index = static_cast<size_t> (show_players_menu.getChoiceFromUser() - 1);
//		coming_players.push_back(players.getItem(index));
//		players.deleteItem(index);
//	}
//	return coming_players;
//}

//void Group::createTeams(uint16_t teams_amount,uint16_t players_in_team_amount)
//{
//	const uint16_t COMING_PLAYERS_AMOUNT = teams_amount * players_in_team_amount;
//	TeamsCreator::createTeams(chooseComingPlayers(COMING_PLAYERS_AMOUNT), teams_amount, players_in_team_amount);
//}
