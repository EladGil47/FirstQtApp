#include "team_player_item_widget.hpp"
#include "app_common.hpp"

#include <QToolButton>

TeamPlayerItemWidget::TeamPlayerItemWidget(std::shared_ptr<Player> player)
{
    if (player)
    {
        m_player = player;
        QString player_name = QString::fromStdString(player->getName());
        initPlayerNameLabel(player_name);
        initRemoveButton();
        initLayout();
    }
}

void TeamPlayerItemWidget ::initPlayerNameLabel(const QString &player_name)
{
    m_player_name_label = new QLabel(player_name);
    m_player_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    m_player_name_label->setStyleSheet(Style::WHITE_TEXT_COLOR);
    m_player_name_label->setAlignment(Qt::AlignHCenter);
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
    m_add_player_button->setStyleSheet(Style::TRANSPARENT_BORDER_BG + Style::BLACK_TEXT_COLOR);
    // connect(m_add_player_button, &QToolButton::doubleClicked, this, &TeamPlayerItemWidget::onAddPlayerClicked);
}

void TeamPlayerItemWidget::onRemoveClicked()
{
    emit removePlayerClickedSignal(m_player->getId());
    if (m_player_name_label)
    {
        delete m_player_name_label;
        m_player_name_label = nullptr;
    }
    if (m_remove_button)
    {
        delete m_remove_button;
        m_remove_button = nullptr;
    }
    initAddButton();
    initAddPlayerButton();

    m_layout->addWidget(m_add_button, 1);
    m_layout->addWidget(m_add_player_button, 20);
}

void TeamPlayerItemWidget::onAddPlayerClicked()
{
    emit std::shared_ptr<Player> player = addPlayerClickedSignal();
    if (player)
    {
        if (m_add_button)
        {
            delete m_add_button;
            m_add_button = nullptr;
        }

        if (m_add_player_button)
        {
            delete m_add_player_button;
            m_add_player_button = nullptr;
        }

        m_player = player;
        QString player_name = QString::fromStdString(player->getName());
        initPlayerNameLabel(player_name);
        initRemoveButton();

        m_layout->addWidget(m_remove_button, 1);
        m_layout->addWidget(m_player_name_label, 20);
    }
}
