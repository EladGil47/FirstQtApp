#ifndef KOHOT_GROUPS_COLLECTION_HPP
#define KOHOT_GROUPS_COLLECTION_HPP

#include "group.hpp"

class GroupsCollection : public BaseCollection<Group>
{
public:
	void display() override;
	std::vector<std::string> getGroupsNames()
	{
		std::vector<std::string> names;
		for (std::shared_ptr<Group> g : m_collection)
		{
			names.push_back(g->getName());
		}
		return names;
	}
};

#endif // KOHOT_GROUPS_COLLECTION_HPP


