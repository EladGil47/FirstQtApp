#ifndef FIRST_QT_APP_INCLUDE_BASE_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_BASE_ITEM_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "app_common.hpp"
#include "editable_label.h"

class BaseItemWidget : public QWidget
{
    Q_OBJECT

private:

void initNameLabel(const QString& name)
{
    m_name_label = new EditableLabel;
    m_name_label->setText(name);
    m_name_label->setAlignment(Qt::AlignLeft);
    m_name_label->setFont(Fonts::ITEM_WIDGET_FONT);
    m_name_label->setMaxLength(MaxValues::ITEM_WIDGET_LABEL_NAME);
}

void initRateLabel(const QString& rate)
{
    m_rate_label = new QLabel(rate);
    m_rate_label->setFont(Fonts::ITEM_WIDGET_FONT);
}


EditableLabel* m_name_label;
QLabel* m_rate_label;

};
#endif // FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
