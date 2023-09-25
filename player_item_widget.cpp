
#include "player_item_widget.h"
#include "app_common.hpp"

#include <QHBoxLayout>

PlayerItemWidget::PlayerItemWidget(std::shared_ptr<Player> player) 
: BasePlayerItemWidget(player)
{
    initEnterButton();
    initRemoveButton();
    setupLayout();

    connect(m_name_label, EditableLabel::finishEditingSig, this, onChangePlayerName);
}

void PlayerItemWidget::initEnterButton()
{
    m_enter_button = new QPushButton("Enter");
    m_enter_button->setFixedSize(Sizes::WIDGET_IN_PLAYER_ITEM_WIDGET);
    m_enter_button->setStyleSheet(Style::BLUE_BUTTON_HOR_LAYOUT);
    connect(m_enter_button, &QPushButton::clicked, this, onEnterButtonClicked);
}

void PlayerItemWidget::initRemoveButton()
{
    m_remove_button = new QPushButton("Remove");
    m_remove_button->setFixedSize(Sizes::WIDGET_IN_PLAYER_ITEM_WIDGET);
    m_remove_button->setStyleSheet(Style::RED_BUTTON_HOR_LAYOUT);
    connect(m_remove_button, &QPushButton::clicked, this, onRemoveButtonClicked);
}

void PlayerItemWidget::setupLayout()
{
    // OR 2 4 1  1
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_name_label);
    layout->addWidget(m_rate_label);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addSpacerItem(spacer);
    layout->addWidget(m_enter_button);
    layout->addWidget(m_remove_button);
}

// slots

void PlayerItemWidget::onEnterButtonClicked()
{
    emit enterButtonClickedSignal(m_player_index);
}
void PlayerItemWidget::onRemoveButtonClicked()
{
    emit removeButtonClickedSignal(m_player_index);
}
void PlayerItemWidget::onChangePlayerName(const QString &name)
{
    emit playerNameChangedSignal(m_player_index, name.toStdString());
}