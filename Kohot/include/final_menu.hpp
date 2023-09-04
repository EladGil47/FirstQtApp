#ifndef KOHOT_FINAL_MENU_HPP
#define KOHOT_FINAL_MENU_HPP

#include "menu.hpp"

class FinalMenu : public Menu
{
public:
	enum class FinalMenuOption { 
		GO_BACK = 1,
		EXIT };

	FinalMenu();
	bool handle() override;

private:
	FinalMenuOption getChoosenOption() {
		return static_cast<FinalMenuOption>(getChoiceFromUser());
	}
};
#endif // KOHOT_FINAL_MENU_HPP