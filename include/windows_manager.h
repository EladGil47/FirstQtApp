#ifndef FIRST_QT_APP_INCLUDE_WINDOW_MANAGER_H
#define FIRST_QT_APP_INCLUDE_WINDOW_MANAGER_H

#include <QMainWindow>
#include <QGuiApplication>
#include <QScreen>
#include "groups_list_window.h"
#include "players_list_window.h"
#include "create_teams_window.h"
#include "display_teams_window.hpp"
#include "groups_collection.hpp"
#include "app_common.hpp"

class WindowsManager : public QMainWindow
{
    Q_OBJECT
public:
    WindowsManager(std::shared_ptr<GroupsCollection> groups_collection = nullptr, QWidget *parent = nullptr);

private slots:
    void setToGroupsListWindow();
    void setToPlayersListWindow(size_t id);
    void setToDisplayTeamsWindow();
    void setToCreateTeamsWindow();

private:
    GroupsListWindow *m_groups_list_window;
    PlayersListWindow *m_players_list_window;
    CreateTeamsWindow *m_create_teams_window;
    DisplayTeamsWindow *m_display_teams_window;
    std::shared_ptr<Group> m_group;
    std::shared_ptr<GroupsCollection> m_groups_collection;

    void setWindow();
    void initPlayersListWindow(size_t id);
    void initGroupsListWindow();
    void initCreateTeamsWindow();
    void initDisplayTeamsWindow();
    void moveWindowToCenter();
};

#endif // FIRST_QT_APP_INCLUDE_WINDOW_MANAGER_H
