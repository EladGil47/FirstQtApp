#include "team_player_item_widget.hpp"

#include <QLabel>
#include <QHBoxLayout>

#include "app_common.hpp"

TeamPlayerItemWidget::TeamPlayerItemWidget(const QString& playerName)
{
    QLabel* player_name_label = new QLabel(playerName);
    player_name_label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    player_name_label->setStyleSheet(Style::WHITE_TEXT_COLOR);
    player_name_label->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(player_name_label);
}