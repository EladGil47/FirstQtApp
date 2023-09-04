#ifndef KOHOT_PLAYERS_SORTER_HPP
#define KOHOT_PLAYERS_SORTER_HPP

#include "player.hpp"

#include <vector>
#include <memory>


class PlayersSorter
{
private:
	static bool compareByRate(std::shared_ptr<Player> a, std::shared_ptr<Player> b);
	static bool compareByName(std::shared_ptr<Player> a, std::shared_ptr<Player> b);
	static uint16_t countGoalKeepers(std::vector<std::shared_ptr<Player>> players);

public:
	enum class SortOptions { NAME, RATE };
	//static void sortBySortOption(std::shared_ptr <std::vector<std::shared_ptr<Player>>> players, SortOptions sort_option);
	static void  sortBySortOption(std::vector<std::shared_ptr<Player>> &players, SortOptions sort_option);

};

#endif //KOHOT_PLAYERS_SORTER_HPP