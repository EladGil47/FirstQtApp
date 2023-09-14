#ifndef FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H
#define FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H

#include <QMainWindow>

#include <QGuiApplication>
#include <QScreen>

#include "mainwindow.h"
#include "group_menu_window.h"
#include "groups_collection.hpp"
#include "app_common.hpp"



class CustomWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow *m_main_window;
    GroupMenuWindow *m_group_menu_window;
    std::shared_ptr<GroupsCollection> m_groups_collection;

    void setGroupMenuWindow(size_t id)
    {
        std::shared_ptr<Group> group = m_groups_collection->getItem(id);
        m_group_menu_window = new GroupMenuWindow(group, this);
        QObject::connect(m_group_menu_window, GroupMenuWindow::onGoBackButtonClickedSignal, this, switchToMainWindowWidget);
    }

    void setMainWindow()
    {
        m_main_window = new MainWindow(m_groups_collection, this);
        QObject::connect(m_main_window, MainWindow::switchToGroupMenuWidgetSignal, this, switchToGroupMenuWidget);
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

    CustomWindow(std::shared_ptr<GroupsCollection> groups_collection = nullptr, QWidget *parent = nullptr) : QMainWindow(parent)
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
        setCentralWidget(m_main_window);
    }

    void switchToGroupMenuWidget(size_t id)
    {
        setGroupMenuWindow(id);
        setCentralWidget(m_group_menu_window);
    }
};

#endif // FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H