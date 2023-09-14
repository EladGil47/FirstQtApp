#include "players_list_window.h"

#include "player_item_widget.h"

#include <QInputDialog>
#include <QDebug>

PlayersListWindow::PlayersListWindow(std::shared_ptr<Group> group, QMainWindow *parent)
    : BaseListManagerWindow(parent), m_group(group)
{
      init();
}

void PlayersListWindow::init() 
{
    setHeaderLabelText(QString::fromStdString(m_group->getName()));
    setListViewerLabelText();
    setCreateNewPlayerButton();
    setCreateTeamsButton();
    setGoBackButton();
    createButtonsHorLayout();
    initList();

    connect(m_header_label,EditableLabel::finishEditingSig,this,setGroupName);

}

void PlayersListWindow::changePlayerName(uint16_t id ,const std::string & name)
{
    m_group->getPlayersCollectionRef().getItem(static_cast<size_t>(id))->setName(name);
}


void PlayersListWindow::setGroupName(const QString & text)
{
    m_group->setName(text.toStdString());
}

void PlayersListWindow::initList()
{
    for (std::shared_ptr<Player> player : m_group->getPlayersCollectionRef().getCollectionRef())
    {
        addItemToList(player);
    }
}

void PlayersListWindow::setCreateNewPlayerButton()
{
    m_create_new_player_button = new QPushButton("Create new player", this);
    m_create_new_player_button->setStyleSheet(BUTTONS_HOR_LAYOUT_STYLE_SHEET);
    connect(m_create_new_player_button, &QPushButton::clicked, this, &PlayersListWindow::onCreateNewPlayerButton);
}

void PlayersListWindow::setCreateTeamsButton()
{
    m_create_teams_button = new QPushButton("Create teams", this);
    m_create_teams_button->setStyleSheet(BUTTONS_HOR_LAYOUT_STYLE_SHEET);
    connect(m_create_teams_button, &QPushButton::clicked, this, &PlayersListWindow::onCreateTeamsClicked);
}

void PlayersListWindow::setGoBackButton()
{
    m_go_back_button = new QPushButton("Go back", this);
    m_go_back_button->setStyleSheet(BUTTONS_HOR_LAYOUT_STYLE_SHEET);
    connect(m_go_back_button, &QPushButton::clicked, this, &PlayersListWindow::onGoBackButton);
}

void PlayersListWindow::setListViewerLabelText()
{
    m_list_viewer_label->setText("Players :");
}

void PlayersListWindow::createButtonsHorLayout()
{
    m_buttons_hor_layout->addStretch(1);
    addButtonToButtonsHorLayout(m_create_new_player_button);
    addButtonToButtonsHorLayout(m_create_teams_button);
    addButtonToButtonsHorLayout(m_go_back_button);
    m_buttons_hor_layout->addStretch(1);
}

void PlayersListWindow::addButtonToButtonsHorLayout(QPushButton * button)
{
    m_buttons_hor_layout->addWidget(button, 2,  Qt::AlignVCenter);
}

void PlayersListWindow::onCreateNewPlayerButton()
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

void PlayersListWindow::onCreateTeamsClicked()
{
    /// Open a window to choose players
    /// Calls team creator
}

void PlayersListWindow::addItemToList(std::shared_ptr<Player> player)
{
    PlayerItemWidget * player_item_widget = new PlayerItemWidget(player,this);
    QListWidgetItem *item = new QListWidgetItem(m_list_viewer_widget);
    item->setSizeHint(player_item_widget->sizeHint());
    m_list_viewer_widget->setItemWidget(item, player_item_widget);
}

void PlayersListWindow::onRemoveButton(size_t id)
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

void PlayersListWindow::onEnterButton(size_t id)
{
 /// Open a window with player attributes
    /// Calls team creator
}

void PlayersListWindow::onGoBackButton()
{
    emit onGoBackButtonClickedSignal();
}

