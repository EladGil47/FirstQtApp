
#include "player_item_widget.h"
#include <QHBoxLayout>

PlayerItemWidget::PlayerItemWidget(std::shared_ptr<Player> player, GroupMenuWindow *parent)
    : QWidget(parent), m_player(player) , m_group_menu_window(parent)
{
    setNameLabel();
    setRateLabel();
    setEnterButton();
    setRemoveButton();
    setupLayout();
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
    size_t player_id = m_player->getId();

    m_enter_button = new QPushButton("Enter");
    m_enter_button->setStyleSheet("text-align: center;"
                                  "background-color: green;"
                                  "border: none;");
    connect(m_enter_button, &QPushButton::clicked, m_group_menu_window, [=]()
            { m_group_menu_window->onEnterButton(player_id); });
}
void PlayerItemWidget::setRemoveButton()
{
    size_t player_id = m_player->getId();

    m_remove_button = new QPushButton("Remove");
    m_remove_button->setStyleSheet("text-align: center;"
                                   "background-color: red;"
                                   "border: none;");
    connect(m_remove_button, &QPushButton::clicked, m_group_menu_window, [=]()
            { m_group_menu_window->onRemoveButton(player_id); });
}

void PlayerItemWidget::setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_name_label, 2);
    layout->addWidget(m_rate_label, 4);
    layout->addWidget(m_enter_button, 1);
    layout->addWidget(m_remove_button, 1);
}
