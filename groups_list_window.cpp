#include "groups_list_window.h"

#include <QInputDialog>
#include <QFont>

#include "group_item_widget.h"

GroupsListWindow::GroupsListWindow(std::shared_ptr<GroupsCollection> groups_collection,QMainWindow *parent)
:
m_groups_collection(groups_collection)
{
    setHeaderLabelText(QString::fromStdString("Welcome To Kohot"));
    setHeaderLabelEditability(false);
    setListLabelText();
    createButtonsHorLayout();
    initList();
}

GroupsListWindow::~GroupsListWindow()
{
}


void GroupsListWindow::initCreateNewGroupButton()
{
    QString text = "Create new group";
    m_create_new_group_button = new QPushButton(text, this);
    m_create_new_group_button->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"     // Green background color
        "    border: 2px solid #4CAF50;"     // Green border
        "    color: white;"                  // White text color
        "    padding: 3px 15px;"              // Padding around the text
        "    font-size: 18px;"              // Font size
        "    font-weight: bold;"            // Bold text
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"    // Darker green on hover
        "    border: 2px solid #45a049;"    // Darker green border on hover
        "}"
    );
    m_create_new_group_button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_create_new_group_button->setToolTip("Click here to create a new group");
    connect(m_create_new_group_button, &QPushButton::clicked, this, &GroupsListWindow::onCreateNewGroupButton);
}

void GroupsListWindow::initList()
{
    for (std::shared_ptr<Group> group : m_groups_collection->getCollectionRef())
    {
        addGroupItemToList(group);
    }
}

void GroupsListWindow::changeGroupName(uint16_t id ,const std::string & name)
{
    m_groups_collection->getItem(static_cast<size_t>(id))->setName(name);
}

void GroupsListWindow::setListLabelText()
{
    m_list_label->setText("Groups :");
}

void GroupsListWindow::createButtonsHorLayout()
{
    m_buttons_hor_layout->addStretch(1);
    initCreateNewGroupButton();
    m_buttons_hor_layout->addWidget(m_create_new_group_button, 2);
    m_buttons_hor_layout->addStretch(1);
}

void GroupsListWindow::addGroupItemToList(std::shared_ptr<Group> group)
{   
    GroupItemWidget * group_item_widget = new GroupItemWidget(group,this);
    QListWidgetItem *item = new QListWidgetItem(m_list_list_widget);
    item->setSizeHint(group_item_widget->sizeHint());
    m_list_list_widget->setItemWidget(item, group_item_widget);
}

// Slots : 

void GroupsListWindow::onCreateNewGroupButton()
{
    bool ok;
    QString userInput = QInputDialog::getText(this, "Create new group", "Enter group name:", QLineEdit::Normal, "", &ok);
    if (ok && !userInput.isEmpty()) {
        // User entered something and pressed OK
        Group::Config group_config;
        group_config.id = static_cast<uint16_t>(m_groups_collection->getSize());
        group_config.name = userInput.toStdString();
        std::shared_ptr<Group> new_group = std::make_shared<Group>(group_config);
        m_groups_collection->addItem(new_group);
        addGroupItemToList(new_group);
    } 
}

void GroupsListWindow::onRemoveGroupButton(size_t id)
{
    QListWidgetItem *itemToRemove = m_list_list_widget->takeItem(id);
    delete itemToRemove;
    m_groups_collection->deleteItem(id);
    for (size_t index = id; index <  m_groups_collection->getSize(); index++)
    {
        m_groups_collection->getItem(index)->setId(static_cast<uint16_t>(index));
    }
    updateList();
}

void GroupsListWindow::onEnterGroupButton(size_t id)
{
    emit setToPlayersListWindowSignal(id);
}