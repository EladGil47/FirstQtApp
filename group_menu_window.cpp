#include "group_menu_window.h"

#include "player_item_widget.h"

#include <QInputDialog>
#include <QDebug>

GroupMenuWindow::GroupMenuWindow(std::shared_ptr<Group> group, QMainWindow *parent)
    : BaseListManagerWindow(parent), m_group(group)
{
      init();
}

void GroupMenuWindow::init() 
{
    setHeaderLabelText();
    setListViewerLabelText();
    createButtonsHorLayout();
    initList();

}

void GroupMenuWindow::initList()
{
    for (std::shared_ptr<Player> player : m_group->getPlayersCollectionRef().getCollectionRef())
    {
        addItemToList(player);
    }
}

// void GroupMenuWindow::updateList()
// {
//     removeAllItemsFromList();
//     initList();
// }

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
    addButtonToButtonsHorLayout(m_go_back_button,&GroupMenuWindow::onGoBackButton);
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
    Player::Config config;

    bool name_user_input_is_ok;
    QString name_user_input = QInputDialog::getText(this, "Create new player", "Enter player name:", QLineEdit::Normal, "", &name_user_input_is_ok);
    if (name_user_input_is_ok && !name_user_input.isEmpty()) {
        config.name = name_user_input.toStdString();

        bool rate_user_input_is_ok;
        double  rate_user_input = QInputDialog::getDouble(this, "Create new player", "Enter player rate:",0,0,7,1,&rate_user_input_is_ok);
        if(rate_user_input_is_ok && rate_user_input >=0)
        {
            config.rate = rate_user_input;

            config.id = static_cast<uint16_t>(m_group->getNumOfPlayers());
            std::shared_ptr<Player> new_player = std::make_shared<Player>(config);
            m_group->getPlayersCollectionRef().addItem(new_player);
            addItemToList(new_player);
        }
    } 
}

void GroupMenuWindow::onCreateTeamsClicked()
{
    /// Open a window to choose players
    /// Calls team creator
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
    updateList();
}

void GroupMenuWindow::onEnterButton(size_t id)
{
 /// Open a window with player attributes
    /// Calls team creator
}

void GroupMenuWindow::onGoBackButton()
{
    emit onGoBackButtonClickedSignal();
}


// TODO Update this class like I did in mainwindow.cpp