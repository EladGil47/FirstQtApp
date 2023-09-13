#ifndef PLAYER_ITEM_WIDGET_H
#define PLAYER_ITEM_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <memory>

#include "player.hpp"
#include "group_menu_window.h"


class PlayerItemWidget : public QWidget
{
    Q_OBJECT

public:
    PlayerItemWidget(std::shared_ptr<Player> player, GroupMenuWindow* parent);

private:

size_t m_player_index;
void setPlayerIndex(size_t index);

void setNameLabel();
void setRateLabel();
void setEnterButton();
void setRemoveButton();
void setupLayout();


std::shared_ptr<Player> m_player;
GroupMenuWindow * m_group_menu_window;

QLabel* m_name_label;
QLabel* m_rate_label;
QPushButton* m_enter_button;
QPushButton* m_remove_button;


public slots:
void onEnterButtonClicked(bool is_clicked);
void onRemoveButtonClicked(bool is_clicked);

};
#endif // PLAYER_ITEM_WIDGET_H
