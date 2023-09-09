#include "group_menu_window.h"

#include <QDebug>


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
void GroupMenuWindow::onGoBackButton()
{
    hide();
    m_parent->show();
}

void GroupMenuWindow::addItemToList(std::shared_ptr<Player> player)
{
    QWidget *list_item_widget = new QWidget;
    QHBoxLayout *player_list_item_layout = new QHBoxLayout(list_item_widget);

    // Create the player_name label
    QString player_name = QString::fromStdString(player->getName());
    QLabel *player_name_label = new QLabel(player_name, this);
    player_name_label->setAlignment(Qt::AlignLeft);
    player_name_label->setFont(QFont("Arial", 16, QFont::Bold));
    player_list_item_layout->addWidget(player_name_label);

    // Create the enter player button
    QPushButton *enter_button = new QPushButton("Enter");
    enter_button->setStyleSheet("text-align: center;"
                                      "background-color: green;");
    player_list_item_layout->addWidget(enter_button);
    connect(enter_button, &QPushButton::clicked, this, [=]()
            { onEnterButton(player->getId()); });

    player_list_item_layout->addSpacing(1);

    // Create the remove player button
    QPushButton *remove_button = new QPushButton("Remove");
    remove_button->setStyleSheet("text-align: center;"
                                       "background-color: red;");
    player_list_item_layout->addWidget(remove_button);
    connect(remove_button, &QPushButton::clicked, this, [=]()
            { onRemoveButton(player->getId()); });

    QListWidgetItem *item = new QListWidgetItem(m_list_viewer_widget);
    item->setSizeHint(list_item_widget->sizeHint());
    m_list_viewer_widget->setItemWidget(item, list_item_widget);
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
