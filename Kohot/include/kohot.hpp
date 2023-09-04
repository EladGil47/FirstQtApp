#ifndef KOHOT_HPP
#define KOHOT_HPP

#include "groups_collection.hpp"
class Kohot
{
public:

	std::shared_ptr<GroupsCollection> getGroupsCollection();

	/**
	 * @brief Load groups from GROUPS_FILE_PATH to m_groups_collection
	 */
	void loadGroups();

	/**
	 * @brief save m_groups_collection on GROUPS_FILE_PATH
	 */
	void saveGroups();

private:
	 const char* GROUPS_FILE_PATH = "Data/groups.json";
	std::shared_ptr<GroupsCollection> m_groups_collection = std::make_shared<GroupsCollection>();
};

#endif //KOHOT_HPP
