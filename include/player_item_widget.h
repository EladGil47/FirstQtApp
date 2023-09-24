#ifndef FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H

#include <QPushButton>

#include <memory>

#include "player.hpp"
#include "base_item_widget.hpp"


class PlayerItemWidget : public BaseItemWidget
{
    Q_OBJECT

public:
    PlayerItemWidget(std::shared_ptr<Player> player);

private:

size_t m_player_index;
void setPlayerIndex(size_t index);


void initEnterButton();
void initRemoveButton();
void setupLayout();


// EditableLabel* m_name_label;
// QLabel* m_rate_label;
QPushButton* m_enter_button;
QPushButton* m_remove_button;


public slots:
void onEnterButtonClicked();
void onRemoveButtonClicked();
void onChangePlayerName(const QString& name);

signals:
void enterButtonClickedSignal(size_t id);
void removeButtonClickedSignal(size_t id);
void playerNameChangedSignal(size_t id,std::string new_name);




};
#endif // FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
