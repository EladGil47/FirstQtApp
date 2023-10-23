#ifndef FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class TeamPlayerItemWidget : public QWidget
{
 Q_OBJECT
public:
    TeamPlayerItemWidget(const QString &playerName);

signals :
void addPlayerSignal();

private slots:
void onRemoveClicked();
void onAddPlayerClicked();

private:
    QLabel *m_player_name_label;
    QPushButton *m_remove_button;
    QHBoxLayout *m_layout;
    QPushButton *m_add_button;
    QPushButton *m_add_player_button;

    void initRemoveButton();
    void initLayout();
    void initAddPlayerButton();
    void initAddButton();



};

#define FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H
#endif // FIRST_QT_APP_INCLUDE_TEAM_PLAYER_ITEM_WIDGET_H