#include "team_list.hpp"
#include <vector>
#include "app_common.hpp"
#include "team_player_item_widget.hpp"

TeamList::TeamList(std::shared_ptr<Team> team)
{
    ListStyles list_styles;

    m_team = team;

    m_labeled_list = new LabeledListWidget();
    m_labeled_list->setListColor(list_styles.getColoredListStyle(team->getId()));

    const QString TEAM_TEXT = "Team";

    team_name_label = new QLabel(TEAM_TEXT + " " + QString::fromStdString(team->getName()));
    team_name_label->setAlignment(Qt::AlignCenter);
    m_labeled_list->addWidgetAboveList(team_name_label);

    for (uint16_t player_index = 0; player_index < m_team->getNumOfPlayers(); player_index++)
    {
        std::shared_ptr<Player> player                  = m_team->getPlayersCollection()->getItem(player_index);
        TeamPlayerItemWidget*   team_player_item_widget = new TeamPlayerItemWidget(player, player_index);
        connect(team_player_item_widget, &TeamPlayerItemWidget::addPlayerClickedSignal, this, &TeamList::onAddPlayerClicked);
        connect(team_player_item_widget, &TeamPlayerItemWidget::removePlayerClickedSignal, this, &TeamList::onRempovePlayerClicked);

        m_labeled_list->addItemToList(team_player_item_widget);
    }

    initAvgRateLabel();
    m_labeled_list->addWidgetBeneathList(m_avg_rate_label);
}

void TeamList::initAvgRateLabel()
{
    const QString AVG_RATE_TEXT       = "Avg. rate";
    double        avg_rate            = m_team->getAverageRate();
    QString       avg_rate_label_text = AVG_RATE_TEXT + " : " + QString::number(avg_rate + 1, 'g', 2);
    m_avg_rate_label                  = new QLabel(avg_rate_label_text);
    m_avg_rate_label->setAlignment(Qt::AlignCenter);
}

void TeamList::updateAvgRateLabel()
{
    const QString AVG_RATE_TEXT       = "Avg. rate";
    double        avg_rate            = m_team->getAverageRate();
    QString       avg_rate_label_text = AVG_RATE_TEXT + " : " + QString::number(avg_rate + 1, 'g', 2);
    m_avg_rate_label->setText(avg_rate_label_text);
}

void TeamList::setAverageRateLabel(const QString& avgRate)
{
    m_avg_rate_label->setText(avgRate);
}

std::shared_ptr<Team> TeamList::getTeam()
{
    return m_team;
}

LabeledListWidget* TeamList::getLabeledListWidget()
{
    return m_labeled_list;
}

std::shared_ptr<Player> TeamList::onAddPlayerClicked(uint16_t player_index_in_team_list)
{
    std::shared_ptr<Player> new_player = nullptr;

    new_player = emit addPlayerClickedSignal(m_team->getId());
    if (new_player)
    {
        m_team->replacePlayer(player_index_in_team_list, new_player);
        updateAvgRateLabel();
    }
    return new_player;
}

void TeamList::onRempovePlayerClicked(uint16_t player_index_in_team_list)
{
    m_team->cleanPlayer(player_index_in_team_list);
    updateAvgRateLabel();
}