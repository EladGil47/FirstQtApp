// checkable_item_widget.hpp
#ifndef FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H

#include "base_player_item_widget.hpp"

#include <QCheckBox>
#include <QMouseEvent>

class CheckablePlayerItemWidget : public BasePlayerItemWidget
{
    Q_OBJECT

public:
    CheckablePlayerItemWidget(std::shared_ptr<Player> player);

    void setIsCheckBoxEnabled(bool state);
    void setCheckState(Qt::CheckState state);
    Qt::CheckState getCheckBoxState();

private:
    QCheckBox *m_is_selected_check_box;
    bool m_is_click_enabled = true;

    void setupLayout();
    void mousePressEvent(QMouseEvent *event);
    void initIsSelectedCheckBox();

private slots:
    void onCheckBoxStateChanged(int state);

signals:
    void checkBoxStateChangedSignal(size_t id, int state);
};

#endif // FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
