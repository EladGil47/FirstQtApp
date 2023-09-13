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
    GroupMenuWindow(std::shared_ptr<Group> group = nullptr,QMainWindow *parent = nullptr);
    
    
    void init() override  ;

private:
    void updateList();
    void initList();

    void setHeaderLabelText() override  ;
    void setListViewerLabelText() override ;
    void createButtonsHorLayout() override;

    QPushButton *m_create_new_player_button = new QPushButton("Create new player", this);
    QPushButton *m_create_teams_button = new QPushButton("Create teams", this);
    QPushButton *m_go_back_button = new QPushButton("Go back", this);

    std::shared_ptr<Group> m_group;

    void addButtonToButtonsHorLayout(
    QPushButton * button,
    void (GroupMenuWindow::*slot)());

    void addItemToList(std::shared_ptr<Player> player);

public slots:
    void onCreateNewPlayerButton();
    void onCreateTeamsClicked();
    void onGoBackButton();
    void onRemoveButton(size_t id);
    void onEnterButton(size_t id);

signals:
    void onGoBackButtonClickedSignal();


};

#endif // FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H