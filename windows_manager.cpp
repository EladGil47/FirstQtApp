#include "windows_manager.h"

WindowsManager::WindowsManager(std::shared_ptr<GroupsCollection> groups_collection)
{
    if (groups_collection)
    {
        m_groups_collection = groups_collection;
        setWindow();
        setToGroupsListWindow();
        show();
    }
}

void WindowsManager::setToGroupsListWindow()
{
    initGroupsListWindow();
    setCentralWidget(m_groups_list_window);
}

void WindowsManager::setToPlayersListWindow(size_t id)
{
    initPlayersListWindow(id);
    setCentralWidget(m_players_list_window);
}

void WindowsManager::setToDisplayTeamsWindow(std::shared_ptr<PlayersCollection> players, size_t group_id)
{
    initDisplayTeamsWindow(players, group_id);
    setCentralWidget(m_display_teams_window);
}

void WindowsManager::setToCreateTeamsWindow(size_t id)
{
    initCreateTeamsWindow(id);
    setCentralWidget(m_create_teams_window);
}

void WindowsManager::setWindow()
{
    QSize window_size(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
    resize(window_size);
    setMinimumSize(window_size);
    setWindowTitle(Settings::WINDOW_TITLE_TEXT);
    setStyleSheet(Settings::WINDOWS_COLOR);
    moveWindowToCenter();
}

void WindowsManager::initPlayersListWindow(size_t id)
{
    m_players_list_window = new PlayersListWindow(m_groups_collection->getItem(id));
    QObject::connect(m_players_list_window, &PlayersListWindow::onGoBackButtonClickedSignal, this, &WindowsManager::setToGroupsListWindow);
    QObject::connect(m_players_list_window, &PlayersListWindow::setToCreateTeamsWindowSignal, this, &WindowsManager::setToCreateTeamsWindow);
    QObject::connect(m_players_list_window, &PlayersListWindow::setToDisplayTeamsWindowSignal, this, &WindowsManager::setToDisplayTeamsWindow);
}

void WindowsManager::initGroupsListWindow()
{
    m_groups_list_window = new GroupsListWindow(m_groups_collection);
    QObject::connect(m_groups_list_window, &GroupsListWindow::setToPlayersListWindowSignal, this, &WindowsManager::setToPlayersListWindow);
    QObject::connect(m_groups_list_window, &GroupsListWindow::setToCreateTeamsWindowSignal, this, &WindowsManager::setToCreateTeamsWindow);
}

void WindowsManager::initCreateTeamsWindow(size_t id)
{
    m_create_teams_window = new CreateTeamsWindow(m_groups_collection->getItem(id));
    QObject::connect(m_create_teams_window, &CreateTeamsWindow::cancelButtonClickedSignal, this, &WindowsManager::setToPlayersListWindow);
    QObject::connect(m_create_teams_window, &CreateTeamsWindow::okButtonClickedSignal, this, &WindowsManager::setToDisplayTeamsWindow);
}

void WindowsManager::initDisplayTeamsWindow(std::shared_ptr<PlayersCollection> players, size_t group_id)
{
    m_display_teams_window = new DisplayTeamsWindow(players, m_groups_collection->getItem(group_id));
    QObject::connect(m_display_teams_window, &DisplayTeamsWindow::okButtonClickedSignal, this, &WindowsManager::setToGroupsListWindow);
    QObject::connect(m_display_teams_window, &DisplayTeamsWindow::goBackButtonClickedSignal, this, &WindowsManager::setToCreateTeamsWindow);
}

void WindowsManager::moveWindowToCenter()
{
    QScreen* primaryScreen  = QGuiApplication::primaryScreen();
    QRect    screenGeometry = primaryScreen->geometry();
    int      x              = (screenGeometry.width() - size().width()) / 2;
    int      y              = (screenGeometry.height() - size().height()) / 2;
    move(x, y);
}
