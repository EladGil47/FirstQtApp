#ifndef FIRST_QT_APP_INCLUDE_players_list_window_H
#define FIRST_QT_APP_INCLUDE_players_list_window_H

#include <QWidget>

#include "group.hpp"
#include <memory>
#include <iostream>

#include "mainwindow.h"

#include "base_list_manager_window.h"

class PlayersListWindow : public BaseListManagerWindow
{
    Q_OBJECT

public:
    PlayersListWindow(std::shared_ptr<Group> group = nullptr,QMainWindow *parent = nullptr);
    void changePlayerName(uint16_t id ,const std::string & name);
    

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

       const QString BUTTONS_HOR_LAYOUT_STYLE_SHEET = 
        "QPushButton {"
        "    background-color: #4CAF50;"     // Green background color
        "    border: 2px solid #4CAF50;"     // Green border
        "    color: white;"                  // White text color
        "    padding: 3px 15px;"            // Padding around the text
        "    font-size: 18px;"              // Font size
        "    font-weight: bold;"            // Bold text
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"    // Darker green on hover
        "    border: 2px solid #45a049;"    // Darker green border on hover
        "}";

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

#endif // FIRST_QT_APP_INCLUDE_players_list_window_H