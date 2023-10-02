#ifndef FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "app_common.hpp"

class TeamPlayerItemWidget : public QWidget
{
public:
    TeamPlayerItemWidget(const QString& playerName)
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
};
#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#endif // 