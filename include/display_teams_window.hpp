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

#include "team_player_item_widget.hpp" 

#include "search_widget.hpp" 

class DisplayTeamsWindow : public QWidget
{
    Q_OBJECT
private:
QHBoxLayout  * m_header_layout; 
QHBoxLayout  * m_teams_hor_layout; 
QHBoxLayout  * m_buttons_layout;

QPushButton *m_ok_button;
QPushButton *m_go_back_button;


std::shared_ptr <PlayersCollection> m_players;
Group::Config m_group_config;

void initHeaderLayout()
{
    m_header_layout = new QHBoxLayout;

    QString group_name =QString::fromStdString( m_group_config.name);
    QLabel *m_header_label = new QLabel(group_name);
    m_header_label->setFont(Fonts::LARGE_FONT);
    m_header_label->setAlignment(Qt::AlignHCenter);

    m_header_layout->addWidget(m_header_label);
}

void initTeamsHorLayout()
{
    m_teams_hor_layout = new QHBoxLayout;
    QString team_text = "Team";
    QString avg_rate = "Avg. rate";
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
        QLabel * team_label = new QLabel(team_text + " " + team_number);
        team_label->setAlignment(Qt::AlignCenter);
        labeled_list->addWidgetAboveList(team_label);
        labeled_list->setListColor(list_styles.getColoredListStyle(team_index));

        for (uint16_t player_index = 0; player_index < players_in_teams_amount; player_index++)
        {
            QString player_name = QString::fromStdString((*teams)[team_index].getPlayersCollection()->getItem(player_index)->getName());
            TeamPlayerItemWidget * team_player_item_widget = new TeamPlayerItemWidget(player_name);
            connect(team_player_item_widget,&TeamPlayerItemWidget::addPlayerSignal,this,&DisplayTeamsWindow::onAddPlayer);
            labeled_list->addItemToList(team_player_item_widget);
        }
        QString avg_rate_label_text = avg_rate + " : " +  QString::number((*teams)[team_index].getAverageRate(),'g',2);
        labeled_list->addLabelbeneathList(avg_rate_label_text,Qt::AlignCenter);

        m_teams_hor_layout->addWidget(labeled_list);
    }
}


void initGoBackButton()
{
    m_go_back_button = new QPushButton("Go Back");
    m_go_back_button->setStyleSheet(Style::GREEN_BUTTON_HOR_LAYOUT);
    connect(m_go_back_button, &QPushButton::clicked, this, &DisplayTeamsWindow::onGoBackButton);
}
void initOkButton()
{
    m_ok_button = new QPushButton("OK");
    m_ok_button->setStyleSheet(Style::GREEN_BUTTON_HOR_LAYOUT);
    connect(m_ok_button, &QPushButton::clicked, this, onOkButton);
}

void initButtonsLayout()
{
    initGoBackButton();
    initOkButton();


    m_buttons_layout = new QHBoxLayout;
    m_buttons_layout->addStretch(1);
    m_buttons_layout->addWidget(m_ok_button,2);
    m_buttons_layout->addStretch(1);
    m_buttons_layout->addWidget(m_go_back_button,2);
    m_buttons_layout->addStretch(1);
}
 
QLabel * resultLabel ;


void initWindowLayout()
{
    QVBoxLayout  * window_layout = new QVBoxLayout(this);
    window_layout->setSpacing(0);
    window_layout->addLayout(m_header_layout);
    window_layout->addStretch(5);
    window_layout->addLayout(m_teams_hor_layout);
    window_layout->addStretch(8);
    window_layout->addLayout(m_buttons_layout);



}
std::shared_ptr <Group> m_group;

QStringList * getGroupPlayersNames()
{
    QStringList * m_group_players_names = new QStringList;

    for (const std::string player_name : m_group->getPlayersCollection().getPlayersNames())
    {
        m_group_players_names->append(QString::fromStdString(player_name));
    }
    return m_group_players_names;
}

public : 
DisplayTeamsWindow(std::shared_ptr <PlayersCollection> players,std::shared_ptr <Group> group)
{
    m_group = group;
    m_group_config = group->getConfig();
    m_players=players;
    initHeaderLayout();
    initTeamsHorLayout();
    initButtonsLayout();
    initWindowLayout();
}

signals:
   void goBackButtonClickedSignal(size_t id);
   void okButtonClickedSignal();


public slots:
void onGoBackButton()
{
  emit goBackButtonClickedSignal(m_group_config.id);
}


void onOkButton()
{
  emit okButtonClickedSignal();

}
private slots:

QString onAddPlayer()
{   
    SearchWidget * m_search_player_dialog  = new SearchWidget(getGroupPlayersNames());

    QString player_name;
    if (m_search_player_dialog->exec() == QDialog::Accepted)
    {
        player_name = m_search_player_dialog->getSearchText();
    }
    return player_name;
}


};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H