#include "windows_manager.h"

WindowsManager::WindowsManager(std::shared_ptr<GroupsCollection> groups_collection, QWidget *parent)
    : QMainWindow(parent)
{
    m_groups_collection = groups_collection;
    setWindow();
    setToGroupsListWindow();
    show();
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

void WindowsManager::setToDisplayTeamsWindow(std::shared_ptr <PlayersCollection> players)
{
    initDisplayTeamsWindow(players);
    setCentralWidget(m_display_teams_window);
}

void WindowsManager::setToCreateTeamsWindow()
{
    initCreateTeamsWindow();
    setCentralWidget(m_create_teams_window);
}

void WindowsManager::setWindow()
{
    QSize window_size(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
    resize(window_size);
    setMinimumSize(window_size);
    setWindowTitle(Settings::WINDOW_TITLE_TEXT);
    setStyleSheet(Settings::BACKGROUND_COLOR);
    moveWindowToCenter();
}

void WindowsManager::initPlayersListWindow(size_t id)
{
    m_group = m_groups_collection->getItem(id);
    m_players_list_window = new PlayersListWindow(m_group);
    QObject::connect(m_players_list_window, &PlayersListWindow::onGoBackButtonClickedSignal, this, &WindowsManager::setToGroupsListWindow);
    QObject::connect(m_players_list_window, &PlayersListWindow::setToCreateTeamsWindowSignal, this, &WindowsManager::setToCreateTeamsWindow);
}

void WindowsManager::initGroupsListWindow()
{
    m_groups_list_window = new GroupsListWindow(m_groups_collection);
    QObject::connect(m_groups_list_window, &GroupsListWindow::setToPlayersListWindowSignal, this, &WindowsManager::setToPlayersListWindow);
}

void WindowsManager::initCreateTeamsWindow()
{
    m_create_teams_window = new CreateTeamsWindow(m_group);
    QObject::connect(m_create_teams_window, &CreateTeamsWindow::cancelButtonClickedSignal, this, &WindowsManager::setToPlayersListWindow);
    QObject::connect(m_create_teams_window, &CreateTeamsWindow::okButtonClickedSignal, this, &WindowsManager::setToDisplayTeamsWindow);
}

void WindowsManager::initDisplayTeamsWindow(std::shared_ptr <PlayersCollection> players)
{
    m_display_teams_window = new DisplayTeamsWindow(players);
}

void WindowsManager::moveWindowToCenter()
{
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    int x = (screenGeometry.width() - size().width()) / 2;
    int y = (screenGeometry.height() - size().height()) / 2;
    move(x, y);
}
