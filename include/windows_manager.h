#ifndef FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H
#define FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H

#include <QMainWindow>

#include <QGuiApplication>
#include <QScreen>

#include "groups_list_window.h"
#include "players_list_window.h"
#include "groups_collection.hpp"
#include "app_common.hpp"



class WindowsManager : public QMainWindow
{
    Q_OBJECT
public:
    GroupsListWindow *m_groups_list_window;
    PlayersListWindow *m_players_list_window;
    std::shared_ptr<GroupsCollection> m_groups_collection;

    void setPlayersListWindow(size_t id)
    {
        std::shared_ptr<Group> group = m_groups_collection->getItem(id);
        m_players_list_window = new PlayersListWindow(group, this);
        QObject::connect(m_players_list_window, PlayersListWindow::onGoBackButtonClickedSignal, this, switchToMainWindowWidget);
    }

    void setMainWindow()
    {
        m_groups_list_window = new GroupsListWindow(m_groups_collection, this);
        QObject::connect(m_groups_list_window, GroupsListWindow::switchToGroupMenuWidgetSignal, this, switchToGroupMenuWidget);
    }

    void initWindowLocation()
    {
        QScreen *primaryScreen = QGuiApplication::primaryScreen();
        QRect screenGeometry = primaryScreen->geometry();
        int x = (screenGeometry.width() - size().width()) / 2;
        int y = (screenGeometry.height() - size().height()) / 2;
        move(x, y);
    }

    void setWindow()
    {
        setWindowTitle(Settings::WINDOW_TITLE_TEXT);
        QSize window_size(Settings::WINDOW_WIDTH,Settings::WINDOW_HEIGHT);
        resize(window_size);
        setMinimumSize(window_size);
        setStyleSheet(Settings::BACKGROUND_COLOR);
    }

    WindowsManager(std::shared_ptr<GroupsCollection> groups_collection = nullptr, QWidget *parent = nullptr) : QMainWindow(parent)
    {
        m_groups_collection = groups_collection;
        initWindowLocation();
        setWindow();
        switchToMainWindowWidget();
        show();
    }
public slots:
    void switchToMainWindowWidget()
    {
        setMainWindow();
        setCentralWidget(m_groups_list_window);
    }

    void switchToGroupMenuWidget(size_t id)
    {
        setPlayersListWindow(id);
        setCentralWidget(m_players_list_window);
    }
};

#endif // FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H