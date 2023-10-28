#ifndef FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H

#include <QPushButton>

#include <memory>

#include "base_player_item_widget.hpp"

class PlayerItemWidget : public BasePlayerItemWidget
{
    Q_OBJECT

private:
    void initEnterButton();
    void initRemoveButton();
    void setupLayout();

    QPushButton *m_enter_button;
    QPushButton *m_remove_button;

private slots:
    void onEnterButtonClicked();
    void onRemoveButtonClicked();
    void onChangePlayerName(const QString &name);

public:
    PlayerItemWidget(std::shared_ptr<Player> player);

signals:
    void enterButtonClickedSignal(size_t id);
    void removeButtonClickedSignal(size_t id);
    void playerNameChangedSignal(size_t id, std::string new_name);
};
#endif // FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
