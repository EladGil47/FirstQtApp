#include "groups_manager_menu.hpp"
#include "group_menu.hpp"
#include "user_interaction.hpp"

GroupsManagerMenu::GroupsManagerMenu(std::shared_ptr<GroupsCollection> groups_collection) :Menu()
{
	std::vector<std::string> options = { "Create Group","Enter Group" ,"Delete Group" ,"Exit" };
	initializeOptions(options);
	initializeHeader("Groups Menu : ");
	m_groups_collection = groups_collection;
}

Group::Config GroupsManagerMenu::getGroupConfigFromUser()
{
	std::cout << "Creating a new group :) \n\n";

	std::string name;
	std::cout << "Please enter name :  ";
	std::cin >> name;

	uint16_t teams_amount  = UserInteraction::getUint16FromUser("Amount of teams", 2);
	uint16_t players_in_team_amount = UserInteraction::getUint16FromUser("Amount of players in a team", 2);

	Group::Config group_config = {
		static_cast<uint16_t>(m_groups_collection->getSize()),
		name,
		teams_amount,
		players_in_team_amount
	};
	return group_config;
}

size_t GroupsManagerMenu::getGroupIndexFromUser()
{
	Menu show_groups_menu;
	show_groups_menu.initializeOptions(m_groups_collection->getGroupsNames());
	size_t index = static_cast<size_t> (show_groups_menu.getChoiceFromUser() - 1);
	return index;
}

void GroupsManagerMenu::onCreateGroup()
{
	Group::Config group_config = getGroupConfigFromUser();
	std::shared_ptr<Group> new_group = std::make_shared<Group>(group_config);
	m_groups_collection->addItem(new_group);
}

void GroupsManagerMenu::moveToGroupMenu(size_t group_index)
{
	GroupMenu group_menu(m_groups_collection->getItem(group_index));
	m_exit_menus =	group_menu.handle();
}

void GroupsManagerMenu::onEnterGroup()
{
	size_t num_of_groups = m_groups_collection->getSize();
	if (num_of_groups > 0)
	{
		size_t group_index = 0;
		if (num_of_groups > 1)
		{
			group_index = getGroupIndexFromUser();
		}
		moveToGroupMenu(group_index);
	}
}

void GroupsManagerMenu::onDeleteGroup()
{
	size_t num_of_groups = m_groups_collection->getSize();
	if (num_of_groups > 0)
	{
		size_t group_index = 0;
		if (num_of_groups > 1)
		{
			group_index = getGroupIndexFromUser();

		}
		m_groups_collection->deleteItem(group_index);
		num_of_groups = m_groups_collection->getSize();
		for (size_t index = group_index ;index < num_of_groups ; index ++)
		{
			m_groups_collection->getItem(index)->setId(static_cast<uint16_t>(index));
		}
	}
}

bool GroupsManagerMenu::handle()
{
	while (!m_exit_menus)
	{
		m_groups_collection->display();
		GroupsManagerMenuOption option = static_cast<GroupsManagerMenuOption>(getChoiceFromUser());
		switch (option)
		{
		case GroupsManagerMenuOption::CREATE_GROUP:
		{
			onCreateGroup();
			break;
		}
		case GroupsManagerMenuOption::ENTER_GROUP:
		{
			onEnterGroup();
			break;
		}
		case GroupsManagerMenuOption::DELETE_GROUP:
		{
			onDeleteGroup();
			break;
		}
		case GroupsManagerMenuOption::EXIT:
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

