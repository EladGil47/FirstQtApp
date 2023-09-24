#ifndef FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H

#include "base_player_item_widget.hpp"

class CheckablePlayerItemWidget : public BasePlayerItemWidget
{
    Q_OBJECT
    
private:


void setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_name_label, 2);
    layout->addWidget(m_rate_label, 4);
}

private slots:

public:
    CheckablePlayerItemWidget(std::shared_ptr<Player> player)
    : BasePlayerItemWidget(player)
    {
        setupLayout();
    }

signals:

};
#endif // FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
