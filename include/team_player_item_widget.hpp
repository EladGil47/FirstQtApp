#ifndef FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class TeamPlayerItemWidget : public QWidget
{
public:
    TeamPlayerItemWidget(const QString &playerName);
private:
QLabel* m_player_name_label;
QPushButton* m_remove_button;
QHBoxLayout* m_layout;

void initRemoveButton();
void initLayout();


private slots:
    void onRemoveClicked();
};
#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#endif // FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H