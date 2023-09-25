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

protected:

BasePlayerItemWidget(std::shared_ptr<Player> player)
{
    Functions::checkNotNull(player, "player in BasePlayerItemWidget ctor");
    setPlayerIndex(static_cast<size_t>(player->getId()));
    initNameLabel(QString::fromStdString(player->getName()));
    initRateLabel(QString::number(player->getRate()));
}

void setPlayerIndex(size_t index)
{
    m_player_index = index;
}

void initNameLabel(const QString& name)
{
    m_name_label = new EditableLabel;
    m_name_label->setText(name);
    m_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_name_label->setMaxLength(MaxValues::ITEM_WIDGET_LABEL_NAME);
}

void initRateLabel(const QString& rate)
{
    m_rate_label = new QLabel(rate);
    m_rate_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
}

size_t m_player_index;
EditableLabel* m_name_label;
QLabel* m_rate_label;

};
#endif // FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
