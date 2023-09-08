#ifndef FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H
#define FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H

#include <QWidget>

#include "group.hpp"
#include <memory>
#include <iostream>

#include "mainwindow.h"

#include "base_list_manager_window.h"

class GroupMenuWindow : public BaseListManagerWindow
{
    Q_OBJECT

public:
    GroupMenuWindow(MainWindow *parent = nullptr, std::shared_ptr<Group> group = nullptr)
        : BaseListManagerWindow(parent), m_group{group}
    {
    }
    
    void init() override  ;

private:
    void setHeaderLabelText() override  ;
    void setListViewerLabelText() override ;
    void createButtonsHorLayout() override;

    QPushButton *create_new_player_button = new QPushButton("Create new player", this);
    
    std::shared_ptr<Group> m_group;

public slots:
    void onCreateNewPlayerButton();

};

#endif // FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H