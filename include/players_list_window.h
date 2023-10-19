#ifndef FIRST_QT_APP_INCLUDE_players_list_window_H
#define FIRST_QT_APP_INCLUDE_players_list_window_H

#include <QWidget>
#include <QPushButton>

#include "editable_label.h"
#include "labeled_list_widget.hpp"

#include "group.hpp"

#include <memory>
class PlayersListWindow  : public QWidget
{
    Q_OBJECT

public:
    PlayersListWindow(std::shared_ptr<Group> group = nullptr);

private:
    void setupLayout();
    void initHeaderLabel();
    void initPlayersList();
    LabeledListWidget *m_players_list;

    void initList() ;

void initPlayersAmountLabel();
void initPlayersAmountLabelText();

    void initButtonsHorLayout() ;

    void initCreateNewPlayerButton();
    void initCreateTeamsButton();
    void initGoBackButton();

    QLabel * m_players_amount_label;
    QPushButton *m_create_new_player_button;
    QPushButton *m_create_teams_button; 
    QPushButton *m_go_back_button;


    EditableLabel *m_header_label ;
    QHBoxLayout *m_buttons_hor_layout;


    std::shared_ptr<Group> m_group;

    void addButtonToButtonsHorLayout(QPushButton * button);
    void addItemToList(std::shared_ptr<Player> player);

public slots:
    void onCreateNewPlayerButton();
    void onCreateTeamsClicked();
    void onGoBackButton();
    void onRemoveButton(size_t id);
    void onEnterButton(size_t id);
    void onPlayerNameChanged(uint16_t id ,const std::string & name);
    void setGroupName(const QString & text);

signals:
    void onGoBackButtonClickedSignal();

    void setToCreateTeamsWindowSignal(size_t id);
};

#endif // FIRST_QT_APP_INCLUDE_players_list_window_H