#ifndef FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H

#include <QPushButton>
#include <QWidget>
#include <memory>
#include <random>
#include <set>
#include "app_common.hpp"
#include "checkable_player_item_widget.hpp"
#include "group.hpp"
#include "labeled_list_widget.hpp"
#include "message_box_util.hpp"

class CreateTeamsWindow : public QWidget
{
    Q_OBJECT

public:
    CreateTeamsWindow(std::shared_ptr<Group> group);

    void initHeaderLabel();
    void initOkButton();
    void initCancelButton();
    void initCheckedPlayersList();
    void initCheckablePlayersList();
    void setupLayout();
    void initListsLayout();
    void initButtonsHorLayout();
    void addPlayerToCheckablePlayersList(std::shared_ptr<Player> player);
    void addPlayerToCheckedPlayersList(std::shared_ptr<Player> player);
    void addAllPlayersToCheckablePlayersList();

private:
    QLabel*            m_header_label;
    QHBoxLayout*       m_lists_layout;
    LabeledListWidget* m_checkable_players_list;
    LabeledListWidget* m_checked_players_list;
    QHBoxLayout*       m_buttons_hor_layout;

    QLabel*                            m_selected_players_amount_label;
    uint32_t                           m_selected_players_amount = 0;
    uint32_t                           m_max_selected_players_amount;
    bool                               m_all_unchecked_disable;
    QPushButton*                       m_ok_button;
    QPushButton*                       m_cancel_button;
    std::shared_ptr<Group>             m_group;
    std::shared_ptr<PlayersCollection> m_selected_players;
    QLabel*                            random_label;
    QCheckBox*                         m_random_select_check_box;

    void disableAllUnchecked();
    void setCheckableItemWidgetCheckBox(size_t index, Qt::CheckState state);
    void enableAllCheckables();
    void removePlayerFromCheckedPlayerList(size_t id);
    void uncheckAll();

signals:
    void cancelButtonClickedSignal(size_t id);
    void okButtonClickedSignal(std::shared_ptr<PlayersCollection> players, size_t id);

public slots:
    void onRemovePlayerButton(size_t player_id);
    void onCancelButtonClicked();
    void onOkButtonClicked();
    void onCheckBoxStateChanged(size_t id, int state);
    void onRandomSelectCheckBoxStateChanged(int state);
};

#endif // FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H
