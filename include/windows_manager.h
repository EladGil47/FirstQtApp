#ifndef FIRST_QT_APP_INCLUDE__WINDOW_MANAGER_H
#define FIRST_QT_APP_INCLUDE__WINDOW_MANAGER_H

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
    WindowsManager(std::shared_ptr<GroupsCollection> groups_collection = nullptr, QWidget *parent = nullptr) : QMainWindow(parent)
    {
        m_groups_collection = groups_collection;
        setWindow();
        setToGroupsListWindow();
        show();
    }

private slots:
    void setToGroupsListWindow()
    {
        initGroupsListWindow();
        setCentralWidget(m_groups_list_window);
    }

    void setToPlayersListWindow(size_t id)
    {
        initPlayersListWindow(id);
        setCentralWidget(m_players_list_window);
    }

    void setToDisplayTeamsWindow()
    {
        initDisplayTeamsWindow();
        setCentralWidget(m_display_teams_window);
    }

    void setToCreateTeamsWindow()
    {
        initCreateTeamsWindow();
        setCentralWidget(m_create_teams_window);

    }

private :
    GroupsListWindow *m_groups_list_window;
    PlayersListWindow *m_players_list_window;
    CreateTeamsWindow *m_create_teams_window;
    DisplayTeamsWindow *m_display_teams_window;


    std::shared_ptr<Group> m_group ;
    std::shared_ptr<GroupsCollection> m_groups_collection;

    void setWindow()
    {
        QSize window_size(Settings::WINDOW_WIDTH,Settings::WINDOW_HEIGHT);
        resize(window_size);
        setMinimumSize(window_size);
        setWindowTitle(Settings::WINDOW_TITLE_TEXT);
        setStyleSheet(Settings::BACKGROUND_COLOR);
        moveWindowToCenter();
    }

    void initPlayersListWindow(size_t id)
    {
        m_group = m_groups_collection->getItem(id);
        m_players_list_window = new PlayersListWindow(m_group);
        QObject::connect(m_players_list_window, PlayersListWindow::onGoBackButtonClickedSignal, this, setToGroupsListWindow);
        QObject::connect(m_players_list_window, PlayersListWindow::setToCreateTeamsWindowSignal, this, setToCreateTeamsWindow);

    }

    void initGroupsListWindow()
    {
        m_groups_list_window = new GroupsListWindow(m_groups_collection);
        QObject::connect(m_groups_list_window, GroupsListWindow::setToPlayersListWindowSignal, this, setToPlayersListWindow);
    }

    void initCreateTeamsWindow()
    {
        m_create_teams_window = new CreateTeamsWindow(m_group);
        QObject::connect(m_create_teams_window, CreateTeamsWindow::cancelButtonClickedSignal, this, setToPlayersListWindow);
        QObject::connect(m_create_teams_window, CreateTeamsWindow::okButtonClickedSignal, this, setToDisplayTeamsWindow);
    }

    void initDisplayTeamsWindow()
    {
        m_display_teams_window = new DisplayTeamsWindow();
    }


    void moveWindowToCenter()
    {
        QScreen *primaryScreen = QGuiApplication::primaryScreen();
        QRect screenGeometry = primaryScreen->geometry();
        int x = (screenGeometry.width() - size().width()) / 2;
        int y = (screenGeometry.height() - size().height()) / 2;
        move(x, y);
    }
};

#endif // FIRST_QT_APP_INCLUDE__WINDOW_MANAGER_H