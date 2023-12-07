#ifndef FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "group.hpp"
#include "team_list.hpp"

class DisplayTeamsWindow : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* m_header_layout;
    QHBoxLayout* m_teams_hor_layout;
    QHBoxLayout* m_buttons_layout;

    QPushButton* m_ok_button;
    QPushButton* m_go_back_button;

    std::shared_ptr<std::vector<std::shared_ptr<Team>>> m_teams;
    std::shared_ptr<Group>                              m_group;
    std::vector<TeamList*>                              m_team_lists;

    bool         hasDuplicates() const;
    void         initHeaderLayout();
    void         initTeamsHorLayout();
    void         initGoBackButton();
    void         initOkButton();
    void         initButtonsLayout();
    void         initWindowLayout();
    QStringList* getGroupPlayersNames();

public:
    DisplayTeamsWindow(std::shared_ptr<PlayersCollection> players, std::shared_ptr<Group> group);

signals:
    void goBackButtonClickedSignal(size_t id);
    void okButtonClickedSignal();

public slots:
    void onGoBackButton();
    void onOkButton();

private slots:
    std::shared_ptr<Player> onAddPlayerClicked(uint16_t id);
};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
