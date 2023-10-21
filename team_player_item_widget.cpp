#include "team_player_item_widget.hpp"
#include "app_common.hpp"

TeamPlayerItemWidget::TeamPlayerItemWidget(const QString& playerName)
{
    m_player_name_label = new QLabel(playerName);
    m_player_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_player_name_label->setStyleSheet(Style::WHITE_TEXT_COLOR);
    m_player_name_label->setAlignment(Qt::AlignHCenter);

    initRemoveButton();
    initLayout();
}

void TeamPlayerItemWidget::initLayout()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_remove_button, 1);
    m_layout->addWidget(m_player_name_label, 20);
}

void TeamPlayerItemWidget::initRemoveButton()
{
    m_remove_button = new QPushButton("X");
    m_remove_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_remove_button->setStyleSheet(Style::RED_BACKGROUND_BLACK_BORDER_WHITE_TEXT);
    connect(m_remove_button, &QPushButton::clicked, this, &TeamPlayerItemWidget::onRemoveClicked);
}

void TeamPlayerItemWidget::onRemoveClicked()
{
    if (m_player_name_label)
    {
        delete m_player_name_label;
        m_player_name_label = nullptr;

        delete m_remove_button;
        m_remove_button = nullptr;

        QPushButton * m_add_button = new QPushButton("+");
        m_add_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
        m_add_button->setStyleSheet(Style::GREEN_COLOR_BLACK_BORDER);

        QPushButton *add_player_button = new QPushButton("Add Player");
        add_player_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
        add_player_button->setStyleSheet(Style::TRANSPARENT_STYLESHEET + Style::BLACK_TEXT_COLOR);

        m_layout->addWidget(m_add_button, 1);
        m_layout->addWidget(add_player_button, 20);
    }
}
