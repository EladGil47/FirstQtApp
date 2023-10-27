#ifndef FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


#include "group.hpp"
#include "teams_creator.hpp"

#include "app_common.hpp"
#include "search_widget.hpp"
#include "team_list.hpp"

class DisplayTeamsWindow : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *m_header_layout;
    QHBoxLayout *m_teams_hor_layout;
    QHBoxLayout *m_buttons_layout;

    QPushButton *m_ok_button;
    QPushButton *m_go_back_button;

    std::shared_ptr<std::vector<std::shared_ptr<Team>>> m_teams;
    std::shared_ptr<Group> m_group;
    std::vector<TeamList *> m_team_lists;

    void initHeaderLayout()
    {
        m_header_layout = new QHBoxLayout;

        QString group_name = QString::fromStdString(m_group->getName());
        QLabel *m_header_label = new QLabel(group_name);
        m_header_label->setFont(Fonts::LARGE_FONT);
        m_header_label->setAlignment(Qt::AlignHCenter);

        m_header_layout->addWidget(m_header_label);
    }

    void initTeamsHorLayout()
    {
        m_teams_hor_layout = new QHBoxLayout;

        size_t teams_amount = static_cast<size_t>(m_group->getTeamsAmount());

        for (size_t team_index = 0; team_index < teams_amount; team_index++)
        {
            TeamList *team_list = new TeamList((*m_teams)[team_index]);
            connect(team_list, &TeamList::addPlayerClickedSignal, this, &DisplayTeamsWindow::onAddPlayerClicked);
            m_team_lists.push_back(team_list);
            m_teams_hor_layout->addWidget(team_list->getLabeledListWidget());
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
        m_buttons_layout->addWidget(m_ok_button, 2);
        m_buttons_layout->addStretch(1);
        m_buttons_layout->addWidget(m_go_back_button, 2);
        m_buttons_layout->addStretch(1);
    }

    void initWindowLayout()
    {
        QVBoxLayout *window_layout = new QVBoxLayout(this);
        window_layout->setSpacing(0);
        window_layout->addLayout(m_header_layout);
        window_layout->addStretch(5);
        window_layout->addLayout(m_teams_hor_layout);
        window_layout->addStretch(8);
        window_layout->addLayout(m_buttons_layout);
    }

    QStringList *getGroupPlayersNames()
    {
        QStringList *m_group_players_names = new QStringList;

        for (const std::string player_name : m_group->getPlayersCollection().getPlayersNames())
        {
            m_group_players_names->append(QString::fromStdString(player_name));
        }
        return m_group_players_names;
    }

public:
    DisplayTeamsWindow(std::shared_ptr<PlayersCollection> players, std::shared_ptr<Group> group)
    {
        m_group = group;
        m_teams = TeamsCreator::createTeams(
            players->getCollection(),
            m_group->getTeamsAmount(),
            m_group->getPlayersInTeamAmount());

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
        emit goBackButtonClickedSignal(m_group->getId());
    }

    void onOkButton()
    {
        bool is_ok_valid = true;
        for (std::shared_ptr<Team> team : (*m_teams))
        {
            if (team->getNumOfPlayers() != static_cast<size_t>(m_group->getPlayersInTeamAmount()))
            {
                is_ok_valid = false;
            }
        }
        if(is_ok_valid)
        emit okButtonClickedSignal();
        else{
            MessageBoxHandler::showMessageBox("Please fill all teams");
        }
    }
private slots:

    std::shared_ptr<Player> onAddPlayerClicked(uint16_t id)
    {
        SearchWidget *m_search_player_dialog = new SearchWidget(getGroupPlayersNames());

        std::shared_ptr<Player> ret_player = nullptr;
        if (m_search_player_dialog->exec() == QDialog::Accepted)
        {
            QString player_name = m_search_player_dialog->getSearchText();
            ret_player = m_group->getPlayerByName(player_name.toStdString());
        }
        return ret_player;
    }
};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H