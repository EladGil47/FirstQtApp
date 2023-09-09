#include "group_menu_window.h"

#include "player_item_widget.h"


#include <QDebug>

GroupMenuWindow::GroupMenuWindow(std::shared_ptr<Group> group, MainWindow *parent)
    : BaseListManagerWindow(parent), m_group{group}
{
    resize(parent->size());
    move(parent->pos());
}

void GroupMenuWindow::init() 
{
    setHeaderLabelText();
    setListViewerLabelText();
    createButtonsHorLayout();
    for (std::shared_ptr<Player> player : m_group->getPlayersCollectionRef().getCollectionRef())
    {
        addItemToList(player);
    }

}

void GroupMenuWindow::setHeaderLabelText() 
{
    QString group_name = QString::fromStdString(m_group->getName()); 
    m_header_label->setText(group_name);
}

void GroupMenuWindow::setListViewerLabelText()
{
    m_list_viewer_label->setText("Players :");
}

void GroupMenuWindow::createButtonsHorLayout()
{
    m_buttons_hor_layout->addStretch(1);
    addButtonToButtonsHorLayout(m_create_new_player_button,&GroupMenuWindow::onCreateNewPlayerButton);
    addButtonToButtonsHorLayout(m_create_teams_button,&GroupMenuWindow::onCreateTeamsClicked);
    addButtonToButtonsHorLayout(m_back_button,&GroupMenuWindow::onGoBackButton);
    m_buttons_hor_layout->addStretch(1);
}

void GroupMenuWindow::addButtonToButtonsHorLayout(
    QPushButton * button,
    void (GroupMenuWindow::*slot)())
{
    m_buttons_hor_layout->addWidget(button, 2,  Qt::AlignVCenter);
    connect(button, &QPushButton::clicked, this, slot);
}

void GroupMenuWindow::onCreateNewPlayerButton()
{
    qDebug() << " Create player window";
}

void GroupMenuWindow::onCreateTeamsClicked()
{
    /// Open a window to choose players
    /// Calls team creator
}

void GroupMenuWindow::onGoBackButton()
{
    m_parent->resize(this->size());
    m_parent->move(this->pos());
    hide();
    m_parent->show();
}

void GroupMenuWindow::addItemToList(std::shared_ptr<Player> player)
{
    PlayerItemWidget * player_item_widget = new PlayerItemWidget(player,this);
    QListWidgetItem *item = new QListWidgetItem(m_list_viewer_widget);
    item->setSizeHint(player_item_widget->sizeHint());
    m_list_viewer_widget->setItemWidget(item, player_item_widget);
}

void GroupMenuWindow::onRemoveButton(size_t id)
{
    m_group->getPlayersCollectionRef().deleteItem(id);
    QListWidgetItem *itemToRemove = m_list_viewer_widget->takeItem(id);
    delete itemToRemove;
    for (size_t index = id; index <  m_group->getNumOfPlayers(); index++)
    {
        m_group->getPlayersCollectionRef().getItem(index)->setId(static_cast<uint16_t>(index));
    }
}

void GroupMenuWindow::onEnterButton(size_t id)
{

}
