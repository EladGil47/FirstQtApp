#ifndef KOHOT_USER_INTERACTION_HPP
#define KOHOT_USER_INTERACTION_HPP

#include <iostream>
#include <string>
#include <cstdint>
#include <limits>


class UserInteraction
{
public:
	static uint16_t getUint16FromUser(const std::string& request_msg, uint16_t min_choice = 0, uint16_t max_choice = 65535)
	{
		uint16_t ret_val;
		std::cout << "\nPlease Enter " << request_msg << ": ";

		while (!(std::cin >> ret_val) || ret_val < min_choice || ret_val > max_choice)
		{
			std::cin.clear();            
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input or out of range, choose again: ";
		}

		return ret_val;
	}
};

#endif //KOHOT_USER_INTERACTION_HPP