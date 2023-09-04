#ifndef KOHOT_HPP
#define KOHOT_HPP

#include "groups_collection.hpp"

class Kohot
{
public:
	void process();
	std::string getWelcomeMsg()
	{
		return WELCOME_MSG;
	}


private:
	 const char* GROUPS_FILE_PATH = "Data/groups.json";
	std::shared_ptr<GroupsCollection> m_groups_collection = std::make_shared<GroupsCollection>();
	const std::string  WELCOME_MSG = " Welcome to Kohot : - ) ";
    const std::string  GOODBYE_MSG = " Good bye : - ) ";
     
	 void loadGroups();
	 void saveGroups();
};

#endif //KOHOT_HPP
