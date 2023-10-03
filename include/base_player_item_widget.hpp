#ifndef FIRST_QT_APP_INCLUDE_BASE_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_BASE_ITEM_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "app_common.hpp"
#include "editable_label.h"
#include "player.hpp"

class BasePlayerItemWidget : public QWidget
{
    Q_OBJECT

public:
    enum SetupLayoutOptions
    {
        None = 0x00,
        NAME = 0x01,
        RATE = 0x02,
        AllOptions = NAME | RATE 
    };

    BasePlayerItemWidget(std::shared_ptr<Player> player)
    {
        if (player)
        {
            m_player = player;
            m_player_index = static_cast<size_t>(player->getId());
        }
    }

void setupLayout(SetupLayoutOptions option)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    switch (option)
    {
    case NAME:
    {
        initNameLabel(QString::fromStdString(m_player->getName()));
        layout->addWidget(m_name_label);
        break;
    }
    case RATE:
    {
        layout->addWidget(m_rate_label);
        break;
    }
    case AllOptions:
    {
        layout->addWidget(m_name_label);
        layout->addWidget(m_rate_label);

        break;
    }
    default:
        break;
    }
    layout->setContentsMargins(0, 0, 0, 0);
}

std::shared_ptr<Player> getPlayer()
{
return m_player;
}

protected:
std::shared_ptr<Player> m_player ;


void initNameLabel(const QString& name)
{
    m_name_label = new QLabel;
    m_name_label->setText(name);
    m_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
}

void initEditableNameLabel(const QString& name)
{
    m_editable_name_label = new EditableLabel;
    m_editable_name_label->setText(name);
    m_editable_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_editable_name_label->setMaxLength(MaxValues::ITEM_WIDGET_LABEL_NAME);
}

void initRateLabel(const QString& rate)
{
    m_rate_label = new QLabel(rate);
    m_rate_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
}

size_t m_player_index;
EditableLabel* m_editable_name_label;
QLabel* m_name_label;

QLabel* m_rate_label;



};
#endif // FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
