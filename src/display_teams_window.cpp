#include "display_teams_window.hpp"

#include <QVBoxLayout>
#include <set>
#include "app_common.hpp"
#include "search_widget.hpp"
#include "teams_creator.hpp"

bool DisplayTeamsWindow::hasDuplicates() const
{
    std::set<std::string> unique_strings;

    for (TeamList* team_list : m_team_lists)
    {
        std::shared_ptr<Team> team = team_list->getTeam();
        for (std::string player_name : team->getPlayersCollection()->getPlayersNames())
            if (!unique_strings.insert(player_name).second)
            {
                return true;
            }
    }

    return false;
}

void DisplayTeamsWindow::initHeaderLayout()
{
    m_header_layout = new QHBoxLayout;

    QString group_name     = QString::fromStdString(m_group->getName());
    QLabel* m_header_label = new QLabel(group_name);
    m_header_label->setFont(Fonts::LARGE_FONT);
    m_header_label->setAlignment(Qt::AlignHCenter);

    m_header_layout->addWidget(m_header_label);
}

void DisplayTeamsWindow::initTeamsHorLayout()
{
    m_teams_hor_layout = new QHBoxLayout;

    size_t teams_amount = static_cast<size_t>(m_group->getTeamsAmount());

    for (size_t team_index = 0; team_index < teams_amount; team_index++)
    {
        TeamList* team_list = new TeamList((*m_teams)[team_index]);
        connect(team_list, &TeamList::addPlayerClickedSignal, this, &DisplayTeamsWindow::onAddPlayerClicked);
        m_team_lists.push_back(team_list);
        m_teams_hor_layout->addWidget(team_list->getLabeledListWidget());
    }
}

void DisplayTeamsWindow::initGoBackButton()
{
    m_go_back_button = new QPushButton("Go Back");
    m_go_back_button->setStyleSheet(Settings::BOTTOM_BUTTONS_LINE_COLOR);
    connect(m_go_back_button, &QPushButton::clicked, this, &DisplayTeamsWindow::onGoBackButton);
}

void DisplayTeamsWindow::initOkButton()
{
    m_ok_button = new QPushButton("OK");
    m_ok_button->setStyleSheet(Settings::BOTTOM_BUTTONS_LINE_COLOR);
    connect(m_ok_button, &QPushButton::clicked, this, &DisplayTeamsWindow::onOkButton);
}

void DisplayTeamsWindow::initButtonsLayout()
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

void DisplayTeamsWindow::initWindowLayout()
{
    QVBoxLayout* window_layout = new QVBoxLayout(this);
    window_layout->setSpacing(0);
    window_layout->addLayout(m_header_layout);
    window_layout->addStretch(5);
    window_layout->addLayout(m_teams_hor_layout);
    window_layout->addStretch(8);
    window_layout->addLayout(m_buttons_layout);
}

QStringList* DisplayTeamsWindow::getGroupPlayersNames()
{
    QStringList* m_group_players_names = new QStringList;

    for (const std::string player_name : m_group->getPlayersCollection().getPlayersNames())
    {
        m_group_players_names->append(QString::fromStdString(player_name));
    }
    return m_group_players_names;
}

DisplayTeamsWindow::DisplayTeamsWindow(std::shared_ptr<PlayersCollection> players, std::shared_ptr<Group> group)
{
    m_group = group;
    if (players->getSize() == 0 || players == nullptr)
    {
        // Create teams with empty players in each team
        m_teams = std::make_shared<std::vector<std::shared_ptr<Team>>>();

        for (uint16_t team_index = 0; team_index < m_group->getTeamsAmount(); team_index++)
        {
            m_teams->push_back(std::make_shared<Team>(team_index));
        }
        for (int player_index = 0; player_index < m_group->getPlayersInTeamAmount(); player_index++)
        {
            for (uint16_t team_index = 0; team_index < m_group->getTeamsAmount(); team_index++)
            {
                std::shared_ptr<Player> player;
                (*m_teams)[team_index]->addPlayer(player);
            }
        }
    }
    else
    {
        m_teams = TeamsCreator::createTeams(
            players->getCollection(),
            m_group->getTeamsAmount(),
            m_group->getPlayersInTeamAmount());
    }

    initHeaderLayout();
    initTeamsHorLayout();
    initButtonsLayout();
    initWindowLayout();
}

void DisplayTeamsWindow::onGoBackButton()
{
    emit goBackButtonClickedSignal(m_group->getId());
}

void DisplayTeamsWindow::onOkButton()
{
    bool is_ok_valid = true;
    if (hasDuplicates())
    {
        is_ok_valid = false;
        MessageBoxHandler::showMessageBox("Same player can not appear twice");
    }
    else
    {
        for (std::shared_ptr<Team> team : (*m_teams))
        {
            if (team->getNumOfPlayers() != static_cast<size_t>(m_group->getPlayersInTeamAmount()))
            {
                is_ok_valid = false;
                MessageBoxHandler::showMessageBox("Please fill all teams");
                break;
            }
        }
    }
    if (is_ok_valid)
    {
        TeamsCreator::serializeTeams(m_teams);
        emit okButtonClickedSignal();
    }
}

std::shared_ptr<Player> DisplayTeamsWindow::onAddPlayerClicked(uint16_t id)
{
    SearchWidget* m_search_player_dialog = new SearchWidget(getGroupPlayersNames());

    std::shared_ptr<Player> ret_player = nullptr;
    if (m_search_player_dialog->exec() == QDialog::Accepted)
    {
        QString player_name = m_search_player_dialog->getSearchText();
        ret_player          = m_group->getPlayerByName(player_name.toStdString());
    }
    return ret_player;
}