#include "team_player_item_widget.hpp"
#include "app_common.hpp"

#include <QToolButton>

TeamPlayerItemWidget::TeamPlayerItemWidget(std::shared_ptr<Player> player, uint16_t player_index_in_team)
    : m_player_index_in_team(player_index_in_team), m_player(std::move(player))
{
    initLayout();
    updateLayout(m_player != nullptr);
}

void TeamPlayerItemWidget::initPlayerNameLabel()
{
    m_player_name_label = std::make_unique<QLabel>(QString::fromStdString(m_player->getName()));
    m_player_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_player_name_label->setStyleSheet(Style::WHITE_TEXT_COLOR);
    m_player_name_label->setAlignment(Qt::AlignHCenter);
}

void TeamPlayerItemWidget::initLayout()
{
    m_layout = std::make_unique<QHBoxLayout>(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
}

void TeamPlayerItemWidget::clearLayout()
{
    while (QLayoutItem* item = m_layout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
        {
            widget->deleteLater();
        }
        delete item;
    }
}

void TeamPlayerItemWidget::updateLayout(bool player_exists)
{
    clearLayout();

    if (player_exists)
    {
        initPlayerNameLabel();
        initRemoveButton();
        m_layout->addWidget(m_remove_button.get(), 1);
        m_layout->addWidget(m_player_name_label.get(), 20);
    }
    else
    {
        initAddButton();
        initAddPlayerButton();
        m_layout->addWidget(m_add_button.get(), 1);
        m_layout->addWidget(m_add_player_button.get(), 20);
    }
}

void TeamPlayerItemWidget::initRemoveButton()
{
    m_remove_button = std::make_unique<QPushButton>("X");
    m_remove_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_remove_button->setStyleSheet(Style::RED_BACKGROUND_BLACK_BORDER_WHITE_TEXT);
    connect(m_remove_button.get(), &QPushButton::clicked, this, &TeamPlayerItemWidget::onRemoveClicked);
}

void TeamPlayerItemWidget::initAddButton()
{
    m_add_button = std::make_unique<QPushButton>("+");
    m_add_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_add_button->setStyleSheet(Style::GREEN_COLOR_BLACK_BORDER);
    connect(m_add_button.get(), &QPushButton::clicked, this, &TeamPlayerItemWidget::onAddPlayerClicked);
}

void TeamPlayerItemWidget::initAddPlayerButton()
{
    m_add_player_button = std::make_unique<QPushButton>("Add Player");
    m_add_player_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_add_player_button->setStyleSheet(Style::TRANSPARENT_STYLESHEET + Style::BLACK_TEXT_COLOR);
    // connect(m_add_player_button.get(), &QToolButton::doubleClicked, this, &TeamPlayerItemWidget::onAddPlayerClicked);
}

void TeamPlayerItemWidget::onRemoveClicked()
{
    emit removePlayerClickedSignal(m_player_index_in_team);
    m_player_name_label.reset();
    m_remove_button.reset();
    updateLayout(false);
}

void TeamPlayerItemWidget::onAddPlayerClicked()
{
    std::shared_ptr<Player> player = addPlayerClickedSignal(m_player_index_in_team);
    if (player)
    {
        m_add_button.reset();
        m_add_player_button.reset();
        m_player = player;
        updateLayout(true);
    }
}
