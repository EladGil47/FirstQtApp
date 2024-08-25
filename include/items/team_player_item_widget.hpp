#ifndef FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <memory>
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
    std::unique_ptr<QLabel>      m_player_name_label;
    std::unique_ptr<QPushButton> m_remove_button;
    std::unique_ptr<QHBoxLayout> m_layout;
    std::unique_ptr<QPushButton> m_add_button;
    std::unique_ptr<QPushButton> m_add_player_button;
    uint16_t                     m_player_index_in_team;
    std::shared_ptr<Player>      m_player;

    void initPlayerNameLabel();
    void initRemoveButton();
    void initLayout();
    void updateLayout(bool player_exists);
    void initAddPlayerButton();
    void initAddButton();
    void clearLayout();
};

#endif // FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H