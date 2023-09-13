
#include "player_item_widget.h"
#include <QHBoxLayout>

PlayerItemWidget::PlayerItemWidget(std::shared_ptr<Player> player, GroupMenuWindow *parent)
    : QWidget(parent), m_player(player), m_group_menu_window(parent)
{
    if (player != nullptr)
    {
        setPlayerIndex(static_cast<size_t>(m_player->getId()));
        setNameLabel();
        setRateLabel();
        setEnterButton();
        setRemoveButton();
        setupLayout();
    }
}

void PlayerItemWidget::setPlayerIndex(size_t index)
{
    m_player_index = index;
}

void PlayerItemWidget::setNameLabel()
{
    QString name = QString::fromStdString(m_player->getName());
    m_name_label = new QLabel(name, this);
    m_name_label->setFont(QFont("Arial", 10, QFont::Bold));
    m_name_label->setStyleSheet("border: none;");
    m_name_label->setAlignment(Qt::AlignLeft);
}

void PlayerItemWidget::setRateLabel()
{
    QString rate = QString::number(m_player->getRate());
    m_rate_label = new QLabel(rate, this);
    m_rate_label->setFont(QFont("Arial", 10, QFont::Bold));
    m_rate_label->setStyleSheet("border: none;");
    m_rate_label->setAlignment(Qt::AlignLeft);
}

void PlayerItemWidget::setEnterButton()
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
void PlayerItemWidget::setRemoveButton()
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

void PlayerItemWidget::onEnterButtonClicked(bool a)
{
 m_group_menu_window->onEnterButton(m_player_index);
}
void PlayerItemWidget::onRemoveButtonClicked(bool a)
{
 m_group_menu_window->onRemoveButton(m_player_index);
}
