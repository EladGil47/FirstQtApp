#ifndef FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H

#include "base_player_item_widget.hpp"

#include <QCheckBox>

class CheckablePlayerItemWidget : public BasePlayerItemWidget
{
    Q_OBJECT
    
private:


void setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_name_label);
    layout->addWidget(m_rate_label);
    layout->addWidget(m_is_selected_check_box);
}


QCheckBox * m_is_selected_check_box ;

void initIsSelectedCheckBox()
{
    m_is_selected_check_box = new QCheckBox;
    connect(m_is_selected_check_box, &QCheckBox::stateChanged, this, onCheckBoxStateChanged);
}

private slots:

    void onCheckBoxStateChanged(int state)
    {
    emit checkBoxStateChangedSignal(state);
    }
    

public:
    CheckablePlayerItemWidget(std::shared_ptr<Player> player)
    : BasePlayerItemWidget(player)
    {
        m_name_label->setEditablity(false);
        initIsSelectedCheckBox();

        setupLayout();
    }
    

signals:
void checkBoxStateChangedSignal(int state);
   
};
#endif // FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
