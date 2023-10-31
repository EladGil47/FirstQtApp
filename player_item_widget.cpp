
#include "player_item_widget.h"
#include "app_common.hpp"

#include <QHBoxLayout>

PlayerItemWidget::PlayerItemWidget(std::shared_ptr<Player> player)
    : BasePlayerItemWidget(player)
{
    initEditableNameLabel(QString::fromStdString(player->getName()));
    connect(m_editable_name_label, &EditableLabel::finishEditingSig, this, &PlayerItemWidget::onChangePlayerName);

    initRateLabel(QString::number(player->getRate(), 'g', 2));
    initRoleLabel(QString::fromStdString(player->getRoleText()));

    initEnterButton();
    initRemoveButton();
    setupLayout();
}

void PlayerItemWidget::initEnterButton()
{
    m_enter_button = new QPushButton("Enter");
    m_enter_button->setFixedSize(Sizes::WIDGET_IN_PLAYER_ITEM_WIDGET);
    m_enter_button->setStyleSheet(Style::BLUE_BUTTON_HOR_LAYOUT);
    connect(m_enter_button, &QPushButton::clicked, this, &PlayerItemWidget::onEnterButtonClicked);
}

void PlayerItemWidget::initRemoveButton()
{
    m_remove_button = new QPushButton("Remove");
    m_remove_button->setFixedSize(Sizes::WIDGET_IN_PLAYER_ITEM_WIDGET);
    m_remove_button->setStyleSheet(Style::RED_BUTTON_HOR_LAYOUT);
    connect(m_remove_button, &QPushButton::clicked, this, &PlayerItemWidget::onRemoveButtonClicked);
}

void PlayerItemWidget::setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_editable_name_label, 1);
    layout->addWidget(m_rate_label, 1);
    layout->addWidget(m_role_label, 1);
    QSpacerItem *space_all_to_end = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addSpacerItem(space_all_to_end);
    layout->addStretch(2);
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
    std::string player_name = name.toStdString();
    m_player->setName(player_name);
    emit playerNameChangedSignal(m_player_index, player_name);
}
