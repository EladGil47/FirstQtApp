#include "groups_collection.hpp"

#include <iomanip>
#include <iostream>

#include "console_colors.hpp"

void GroupsCollection::display()
{
	std::cout << std::left << "Groups:" << std::endl;

	if (!m_collection.empty())
	{
		std::cout << std::left << std::setw(5) << "#"
			<< std::setw(20) << "Name"
			<< std::endl;

		uint16_t iteration_number = 1;
		for (std::shared_ptr<Group>  group : m_collection)
		{
			Group::Config group_config = group->getConfig();
			std::cout << std::left
				<< std::setw(5) << iteration_number
				<< std::setw(20) << group_config.name
				<< std::endl;
			iteration_number++;
		}
	}
	else
	{
		std::cout << "There is no groups\n";
	}

}
