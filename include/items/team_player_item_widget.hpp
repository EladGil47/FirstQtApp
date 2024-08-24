#ifndef FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "player.hpp"

class TeamPlayerItemWidget : public QWidget
{
    Q_OBJECT
public:
    TeamPlayerItemWidget(std::shared_ptr<Player> player, uint16_t player_index_in_team);

signals:
    std::shared_ptr<Player> addPlayerClickedSignal(uint16_t player_index_in_team_list);
    void                    removePlayerClickedSignal(uint16_t player_id);

private slots:
    void onRemoveClicked();
    void onAddPlayerClicked();

private:
    QLabel*                 m_player_name_label;
    QPushButton*            m_remove_button;
    QHBoxLayout*            m_layout;
    QPushButton*            m_add_button;
    QPushButton*            m_add_player_button;
    std::shared_ptr<Player> m_player;

    uint16_t m_player_index_in_team;

    void initPlayerNameLabel();
    void initRemoveButton();
    void initLayout();
    void updateLayout(bool player_exists);
    void initAddPlayerButton();
    void initAddButton();
};

#endif // FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H