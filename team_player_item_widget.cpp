#include "team_player_item_widget.hpp"
#include "app_common.hpp"

#include <QToolButton>

TeamPlayerItemWidget::TeamPlayerItemWidget(std::shared_ptr<Player> player, uint16_t player_index_in_team)
{
    m_player_index_in_team = player_index_in_team;
    m_player               = player;
    initLayout();
    player ? updateLayout(true) : updateLayout(false);
}

void TeamPlayerItemWidget ::initPlayerNameLabel()
{
    m_player_name_label = new QLabel(QString::fromStdString(m_player->getName()));
    m_player_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_player_name_label->setStyleSheet(Style::WHITE_TEXT_COLOR);
    m_player_name_label->setAlignment(Qt::AlignHCenter);
}

void TeamPlayerItemWidget::initLayout()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
}

void TeamPlayerItemWidget::updateLayout(bool player_exists)
{
    if (player_exists)
    {
        initPlayerNameLabel();
        initRemoveButton();
        m_layout->addWidget(m_remove_button, 1);
        m_layout->addWidget(m_player_name_label, 20);
    }
    else
    {
        initAddButton();
        initAddPlayerButton();
        m_layout->addWidget(m_add_button, 1);
        m_layout->addWidget(m_add_player_button, 20);
    }
}

void TeamPlayerItemWidget::initRemoveButton()
{
    m_remove_button = new QPushButton("X");
    m_remove_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_remove_button->setStyleSheet(Style::RED_BACKGROUND_BLACK_BORDER_WHITE_TEXT);
    connect(m_remove_button, &QPushButton::clicked, this, &TeamPlayerItemWidget::onRemoveClicked);
}

void TeamPlayerItemWidget::initAddButton()
{
    m_add_button = new QPushButton("+");
    m_add_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_add_button->setStyleSheet(Style::GREEN_COLOR_BLACK_BORDER);
    connect(m_add_button, &QPushButton::clicked, this, &TeamPlayerItemWidget::onAddPlayerClicked);
}

void TeamPlayerItemWidget::initAddPlayerButton()
{
    m_add_player_button = new QPushButton("Add Player");
    m_add_player_button->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_add_player_button->setStyleSheet(Style::TRANSPARENT_STYLESHEET + Style::BLACK_TEXT_COLOR);
    // connect(m_add_player_button, &QToolButton::doubleClicked, this, &TeamPlayerItemWidget::onAddPlayerClicked);
}

void TeamPlayerItemWidget::onRemoveClicked()
{
    emit removePlayerClickedSignal(m_player_index_in_team);
    if (m_player_name_label)
    {
        delete m_player_name_label;
    }
    if (m_remove_button)
    {
        delete m_remove_button;
    }
    updateLayout(false);
}

void TeamPlayerItemWidget::onAddPlayerClicked()
{
    emit std::shared_ptr<Player> player = addPlayerClickedSignal(m_player_index_in_team);
    if (player)
    {
        if (m_add_button)
        {
            delete m_add_button;
        }

        if (m_add_player_button)
        {
            delete m_add_player_button;
        }

        m_player = player;

        updateLayout(true);
    }
}
