#ifndef FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include "app_common.hpp"

#include "base_list_manager_window.h"
#include "labeled_list_widget.hpp"



#include "players_collection.hpp"

#include "teams_creator.hpp"



class DisplayTeamsWindow : public QWidget
{
    Q_OBJECT

public : 
DisplayTeamsWindow(std::shared_ptr <PlayersCollection> players)
{
    // First list is already exits
    QHBoxLayout  * m_teams_hor_layout = new QHBoxLayout(this);


	std::shared_ptr <std::vector<Team>> m_teams;

    QString team_text = "Team";
    size_t teams_amount = 3;
    size_t players_in_teams_amount = 5;

    // TODO NEED TO FIX 
    // I THINK : addItemToList function
    m_teams = TeamsCreator::createTeams(players->getCollection(), teams_amount, 5);
    for (size_t team_index = 0; team_index < teams_amount; team_index++)
    {
        LabeledListWidget *labeled_list = new LabeledListWidget();
        QString team_number = QString::number(team_index + 1);
        labeled_list->addLabel(team_text + " " + team_number + " : ");
        m_teams_hor_layout->addWidget(labeled_list);
        for (uint16_t player_index = 0; player_index < players_in_teams_amount; player_index++)
        {
            QString player_name = QString::fromStdString((*m_teams)[team_index].getPlayersCollectionRef().getItem(player_index)->getName());
            qDebug() << player_name;
            QLabel  * player_name_label  = new QLabel(player_name);
            labeled_list->addItemToList(player_name_label);
        }
    }
}

};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H