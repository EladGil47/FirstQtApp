
#include "player_item_widget.h"
#include "app_common.hpp"

#include <QHBoxLayout>

PlayerItemWidget::PlayerItemWidget(std::shared_ptr<Player> player)
{
    Functions::checkNotNull(player, "player in PlayerItemWidget ctor");
    setPlayerIndex(static_cast<size_t>(player->getId()));

    initNameLabel(QString::fromStdString(player->getName()));
    initRateLabel(QString::number(player->getRate()));

    initEnterButton();
    initRemoveButton();
    setupLayout();

    connect(m_name_label, EditableLabel::finishEditingSig, this, onChangePlayerName);
}

void PlayerItemWidget::setPlayerIndex(size_t index)
{
    m_player_index = index;
}

void PlayerItemWidget::initEnterButton()
{
    m_enter_button = new QPushButton("Enter");
    m_enter_button->setStyleSheet(
   "QPushButton {"
    "    background-color: #0074CC;"    /* Blue background color */
    "    border: 2px solid #0074CC;"    /* Blue border */
    "    color: white;"                  /* White text color */
    "    padding: 1px 20px;"             /* Reduced vertical padding, same horizontal padding */
    "    font-size: 10px;"               /* Font size */
    "    font-weight: bold;"             /* Bold text */
    "}"
    "QPushButton:hover {"
    "    background-color: #005FAA;"    /* Darker blue on hover */
    "    border: 2px solid #005FAA;"    /* Darker blue border on hover */
    "}"
                                  );
    connect(m_enter_button, &QPushButton::clicked, this, onEnterButtonClicked);
}

void PlayerItemWidget::initRemoveButton()
{
    m_remove_button = new QPushButton("Remove");
    m_remove_button->setStyleSheet(
        "QPushButton {"
    "    background-color: #FF0000;"   /* Red background color */
    "    border: 2px solid #FF0000;"   /* Red border */
    "    color: white;"                /* White text color */
    "    padding: 1px 20px;"          /* Padding around the text */
    "    font-size: 10px;"             /* Font size */
    "    font-weight: bold;"           /* Bold text */
    "}"

    "QPushButton:hover {"
    "    background-color: #FF3333;"   /* Darker red on hover */
    "    border: 2px solid #FF3333;"   /* Darker red border on hover */
    "}"
                                   );
    connect(m_remove_button, &QPushButton::clicked, this, onRemoveButtonClicked);
}

void PlayerItemWidget::setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_name_label, 2);
    layout->addWidget(m_rate_label, 4);
    layout->addWidget(m_enter_button, 1);
    layout->addWidget(m_remove_button, 1);
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