#ifndef FIRST_QT_APP_INCLUDE_BASE_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_BASE_ITEM_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>



#include "app_common.hpp"
#include "editable_label.h"
#include "player.hpp"

class BasePlayerItemWidget : public QWidget
{
    Q_OBJECT

public:
    enum SetupLayoutOptions  : int
    {
        None = 0x00,
        NAME = 0x01,
        RATE = 0x02,
        REMOVE = 0x04,
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

void setupLayout(int x)
{
    SetupLayoutOptions option = static_cast<SetupLayoutOptions>(x);
    QHBoxLayout *layout = new QHBoxLayout(this);
    if(option & REMOVE)
    {
        initRemoveButton();
        layout->addWidget(m_remove_button,1);
    }
    if(option & NAME)
    {
        initNameLabel(QString::fromStdString(m_player->getName()));
        layout->addWidget(m_name_label,24);
    }
    if(option & RATE)
    {
        initRateLabel(QString::number(m_player->getRate()));
        layout->addWidget(m_rate_label,24);
    }
    layout->setContentsMargins(5, 0, 0, 0);
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

void initRemoveButton()
{
    m_remove_button = new QPushButton("X");
    m_remove_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_remove_button->setStyleSheet(Style::RED_BACKGROUND_BLACK_BORDER_WHITE_TEXT + "color: white;");
    connect(m_remove_button, &QPushButton::clicked, this, &BasePlayerItemWidget::onRemoveButtonClicked);
}

size_t m_player_index;
EditableLabel* m_editable_name_label;
QLabel* m_name_label;
QLabel* m_rate_label;
QPushButton* m_remove_button;

private slots:
void onRemoveButtonClicked()
{
    emit removeButtonClickedSignal(m_player_index);
}



signals:
void removeButtonClickedSignal(size_t m_player_index);




};
#endif // FIRST_QT_APP_INCLUDE_PLAYER_ITEM_WIDGET_H
