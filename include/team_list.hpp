#ifndef FIRST_QT_APP_TEAM_LIST_H
#define FIRST_QT_APP_TEAM_LIST_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include "labeled_list_widget.hpp"
#include "team.hpp"

class TeamList : public QWidget
{
    Q_OBJECT
public:
    TeamList(std::shared_ptr<Team> team);

    void addPlayer(std::shared_ptr<Player> player);
    void setAverageRateLabel(const QString &m_avg_rate_label);
    LabeledListWidget *getLabeledListWidget();

private:
    LabeledListWidget *m_labeled_list;
    QLabel *team_name_label;
    QLabel *m_avg_rate_label;

    std::shared_ptr<Team> m_team;

    void initAvgRateLabel();
    void updateAvgRateLabel();

private slots:
    std::shared_ptr<Player> onAddPlayerClicked();
    void onRempovePlayerClicked(uint16_t player_id);

signals:
    std::shared_ptr<Player> addPlayerClickedSignal(uint16_t id);
};

#endif // FIRST_QT_APP_TEAM_LIST_H
