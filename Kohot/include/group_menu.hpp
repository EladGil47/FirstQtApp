#ifndef KOHOT_GROUP_MENU_HPP
#define KOHOT_GROUP_MENU_HPP

#include "menu.hpp"
#include "group.hpp"
#include "team.hpp"

#include <memory>

class GroupMenu : public Menu
{
public:
	enum class GroupMenuOption {
		ADD_PLAYER = 1,
		DELETE_PLAYER,
		CREATE_TEAMS,
		CHANGE_GROUP_NAME,
		GO_BACK,
		EXIT 
	};
	GroupMenu(std::shared_ptr<Group> group);

	bool handle() override;

private:
	GroupMenuOption getChoosenOption() {
		return static_cast<GroupMenuOption>(getChoiceFromUser());
	}
	std::shared_ptr<Group> m_group;
	std::shared_ptr <std::vector<Team>> m_teams;

	void moveToFinalMenu();

	void onDeletePlayer();
	size_t getPlayerIndexFromUser();
	std::vector<std::shared_ptr<Player>> chooseComingPlayers(uint16_t coming_players_amount);

	uint16_t getTeamsAmountFromUser();
	uint16_t getPlayersInTeamAmountFromUser(uint16_t teams_amount);


};

#endif //KOHOT_GROUP_MENU_HPP





