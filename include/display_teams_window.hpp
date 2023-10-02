#ifndef FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "app_common.hpp"

#include "labeled_list_widget.hpp"
#include "players_collection.hpp"
#include "teams_creator.hpp"
#include "group.hpp"




class DisplayTeamsWindow : public QWidget
{
    Q_OBJECT
private:
QHBoxLayout  * m_header_layout; 
QHBoxLayout  * m_teams_hor_layout; 
QHBoxLayout  * m_buttons_layout;

QPushButton *m_go_back_button;

std::shared_ptr <PlayersCollection> m_players;
Group::Config m_group_config;

void initHeaderLayout()
{
    m_header_layout = new QHBoxLayout;

    QString group_name =QString::fromStdString( m_group_config.name);
    QLabel *m_header_label = new QLabel(group_name);
    m_header_label->setFont(Fonts::HEADER_LABEL_FONT);
    m_header_label->setAlignment(Qt::AlignHCenter);

    m_header_layout->addWidget(m_header_label);
}

void initTeamsHorLayout()
{
    m_teams_hor_layout = new QHBoxLayout;
    QString team_text = "Team";
    QString avg_rate = "Avarage rate :";
    ListStyles list_styles;

    std::shared_ptr<std::vector<Team>> teams = TeamsCreator::createTeams(
        m_players->getCollection(),
        m_group_config.teams_amount,
        m_group_config.players_in_team_amount);

    size_t teams_amount = static_cast<size_t>(m_group_config.teams_amount);
    size_t players_in_teams_amount = static_cast<size_t>(m_group_config.players_in_team_amount);
    for (size_t team_index = 0; team_index < teams_amount; team_index++)
    {
        LabeledListWidget *labeled_list = new LabeledListWidget();
        QString team_number = QString::number(team_index + 1);
        labeled_list->addLabel(team_text + " " + team_number ,Qt::AlignCenter);
        labeled_list->setListColor(list_styles.getColoredListStyle(team_index));

        for (uint16_t player_index = 0; player_index < players_in_teams_amount; player_index++)
        {
            QString player_name = QString::fromStdString((*teams)[team_index].getPlayersCollection()->getItem(player_index)->getName());
            QLabel *player_name_label = new QLabel(player_name);
            player_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
            player_name_label->setStyleSheet(Style::WHITE_TEXT_COLOR);
            labeled_list->addItemToList(player_name_label);
        }

        QHBoxLayout *avg_rate_layout = new QHBoxLayout;

        QLabel *avg_rate_label = new QLabel(avg_rate);
        avg_rate_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);


        QString team_rate = QString::number((*teams)[team_index].getAverageRate());
        QLabel *team_rate_label = new QLabel(team_rate);
        team_rate_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);

        avg_rate_layout->addWidget(avg_rate_label);
        avg_rate_layout->addWidget(team_rate_label);
        avg_rate_layout->addStretch(10);


        
        labeled_list->addLayout(avg_rate_layout);

        m_teams_hor_layout->addWidget(labeled_list);
    }
}


void initGoBackButton()
{
    m_go_back_button = new QPushButton("Go back");
    m_go_back_button->setStyleSheet(Style::GREEN_BUTTON_HOR_LAYOUT);
    connect(m_go_back_button, &QPushButton::clicked, this, onGoBackButton);
}

void initButtonsLayout()
{
    initGoBackButton();

    m_buttons_layout = new QHBoxLayout;
    m_buttons_layout->addStretch(1);
    m_buttons_layout->addWidget(m_go_back_button);
    m_buttons_layout->addStretch(1);
}


    
void initWindowLayout()
{
    QVBoxLayout  * window_layout = new QVBoxLayout(this);
    window_layout->setSpacing(0);
    window_layout->addLayout(m_header_layout);
    window_layout->addStretch(5);
    window_layout->addLayout(m_teams_hor_layout);
    window_layout->addStretch(20);
    window_layout->addLayout(m_buttons_layout);

}

public : 
DisplayTeamsWindow(std::shared_ptr <PlayersCollection> players,Group::Config group_config)
{
    m_group_config = group_config;
    m_players=players;
    initHeaderLayout();
    initTeamsHorLayout();
    initButtonsLayout();
    initWindowLayout();
}

signals:
   void goBackButtonClickedSignal();

public slots:
void onGoBackButton()
{
  emit goBackButtonClickedSignal();
}




};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H