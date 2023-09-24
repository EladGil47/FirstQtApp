#ifndef FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H

#include <QWidget>
#include "base_list_manager_window.h"
#include "group.hpp"
#include <memory>

#include "checkable_player_item_widget.hpp"


class CreateTeamsWindow : public BaseListManagerWindow
{
    Q_OBJECT

public:
    std::shared_ptr<Group> m_group;
    CreateTeamsWindow(std::shared_ptr<Group> group = nullptr,QMainWindow *parent = nullptr) :  BaseListManagerWindow(parent)
    {
        m_group = group ;
        m_header_label->setEditablity(false);
        setHeaderLabelText(QString::fromStdString(group->getName()));
        setListLabelText();
        initList();
    }
    void setListLabelText() override
    {
        m_list_label->setText("Check Players :");
    }
    void createButtonsHorLayout() override
    {

    }
    void addItemToList(std::shared_ptr<Player> player)
    {
        CheckablePlayerItemWidget *player_item_widget = new CheckablePlayerItemWidget(player);
        QListWidgetItem *item = new QListWidgetItem(m_list_list_widget);
        item->setSizeHint(player_item_widget->sizeHint());
        m_list_list_widget->setItemWidget(item, player_item_widget);
    }

    void initList() override
    {
        for (std::shared_ptr<Player> player : m_group->getPlayersCollectionRef().getCollectionRef())
        {
            addItemToList(player);
        }
    }
};



#endif // FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H