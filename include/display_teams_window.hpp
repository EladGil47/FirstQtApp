#ifndef FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include "app_common.hpp"

#include "base_list_manager_window.h"


#include "players_collection.hpp"

#include "teams_creator.hpp"



class DisplayTeamsWindow : public BaseListManagerWindow
{
    Q_OBJECT

public : 
DisplayTeamsWindow(std::shared_ptr <PlayersCollection> players)
{
    initBaseWindowLayout();
    QListWidget * sss = new QListWidget;
    // sss->setStyleSheet(Style::LIST);
    m_list_list_layout->addWidget(sss);

   int teams_amount  = 3;
	std::shared_ptr <std::vector<Team>> m_teams;


    m_teams = TeamsCreator::createTeams(players->getCollection(), teams_amount, 5);
    for (uint16_t team_index = 0; team_index < teams_amount; team_index++)
    {
        std::cout << "Team " << team_index + 1 << " : " << std::endl;
        (*m_teams)[team_index].displayTeam();
        std::cout << std::endl;
    }
}


};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H