#ifndef KOHOT_GROUPS_MANAGER_MENU_HPP
#define KOHOT_GROUPS_MANAGER_MENU_HPP

#include "menu.hpp"
#include "groups_collection.hpp"

class GroupsManagerMenu : public Menu
{
public:
	GroupsManagerMenu(std::shared_ptr<GroupsCollection> groups_collection);
	bool handle() override;

private:
	enum class GroupsManagerMenuOption {
		CREATE_GROUP = 1,
		ENTER_GROUP,
		DELETE_GROUP,
		EXIT
	};
	
	std::shared_ptr<GroupsCollection> m_groups_collection;

	void onCreateGroup();
	void onEnterGroup();
	void onDeleteGroup();

	size_t getGroupIndexFromUser();
	Group::Config getGroupConfigFromUser();

	void moveToGroupMenu(size_t group_index);
	Group::Config k();

};

#endif // KOHOT_GROUPS_MANAGER_MENU_HPP