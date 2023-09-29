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
    sss->setStyleSheet(Style::LIST);
    m_list_list_layout->addWidget(sss);

    TeamsCreator::createTeams(players->getCollection(),3,5);
}


};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H