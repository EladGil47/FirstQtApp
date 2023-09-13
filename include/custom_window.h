#ifndef FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H
#define FIRST_QT_APP_INCLUDE_CUSTOM_WINDOW_H

#include <QMainWindow>

#include <QGuiApplication>
#include <QScreen>

#include "mainwindow.h"
#include "group_menu_window.h"

#include "groups_collection.hpp"

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

    void setWindow()
    {
        QScreen *primaryScreen = QGuiApplication::primaryScreen();
        QRect screenGeometry = primaryScreen->geometry();
        int x = (screenGeometry.width() - size().width()) / 2;
        int y = (screenGeometry.height() - size().height()) / 2;
        move(x, y);

        const QString WINDOW_TITLE = "Kohot";
        setWindowTitle(WINDOW_TITLE);
        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 400;
        QSize window_size(WINDOW_WIDTH, WINDOW_HEIGHT);
        resize(window_size);
        setMinimumSize(window_size);
        setObjectName("MainWindowWidget");
        QString window_widget_stylesheet =
            "QWidget#MainWindowWidget { background-color : #FFFFBF}";
        setStyleSheet(window_widget_stylesheet);
    }

     CustomWindow(std::shared_ptr<GroupsCollection> groups_collection = nullptr, QWidget *parent = nullptr) : QMainWindow(parent)
    {
        m_groups_collection = groups_collection;
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