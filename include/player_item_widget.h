#ifndef FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <memory>

#include "player.hpp"
#include "players_list_window.h"


class PlayerItemWidget : public QWidget
{
    Q_OBJECT

public:
    PlayerItemWidget(std::shared_ptr<Player> player, PlayersListWindow* parent);

private:

size_t m_player_index;
void setPlayerIndex(size_t index);

void setNameLabel();
void setRateLabel();
void setEnterButton();
void setRemoveButton();
void setupLayout();


std::shared_ptr<Player> m_player;
PlayersListWindow * m_players_list_window;

EditableLabel* m_name_label;
QLabel* m_rate_label;
QPushButton* m_enter_button;
QPushButton* m_remove_button;


public slots:
void onEnterButtonClicked(bool is_clicked);
void onRemoveButtonClicked(bool is_clicked);
void onChangePlayerName(const QString& name);


};
#endif // FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
