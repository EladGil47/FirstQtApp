#ifndef FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H
#define FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "group.hpp"
#include <memory>
#include <iostream>

#include "mainwindow.h"


class GroupMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    GroupMenuWindow(MainWindow *parent = nullptr, std::shared_ptr<Group> group = nullptr)
        : QMainWindow(parent)
    {
        m_group = group;
        setWindowTitle(parent->WINDOW_TITLE);
        resize(parent->WINDOW_WIDTH, parent->WINDOW_HEIGHT);
        setWindowContent();
    }

private:
    std::shared_ptr<Group> m_group;
    QWidget *m_group_menu_window_widget = new QWidget(this);
    QVBoxLayout *m_group_menu_ver_layout = new QVBoxLayout;


    void createGroupMenuLayout();
    // void createGroupNameLabel();

    void setWindowContent();
};

#endif // FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H