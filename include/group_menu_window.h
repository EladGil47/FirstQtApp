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

private:
    void init() override  ;
    void initList() override;
    void setListViewerLabelText() override ;
    void createButtonsHorLayout() override;

    void setCreateNewPlayerButton();
    void setCreateTeamsButton();
    void setGoBackButton();


    QPushButton *m_create_new_player_button;
    QPushButton *m_create_teams_button; 
    QPushButton *m_go_back_button;

    std::shared_ptr<Group> m_group;

    void addButtonToButtonsHorLayout(QPushButton * button);

    void addItemToList(std::shared_ptr<Player> player);

public slots:
    void onCreateNewPlayerButton();
    void onCreateTeamsClicked();
    void onGoBackButton();
    void onRemoveButton(size_t id);
    void onEnterButton(size_t id);
    void setGroupName(const QString & text);

signals:
    void onGoBackButtonClickedSignal();
    


};

#endif // FIRST_QT_APP_INCLUDE_GROUP_MENU_WINDOW_H