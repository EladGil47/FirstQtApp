#include "mainwindow.h"

#include <QInputDialog>
#include <QFont>

#include "group_menu_window.h"
#include "group_item_widget.h"


MainWindow::MainWindow(QWidget *parent,std::shared_ptr<GroupsCollection> groups_collection):BaseListManagerWindow(parent)
{
    m_groups_collection = groups_collection;
    init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init() 
{
    setHeaderLabelText();
    setListViewerLabelText();
    createButtonsHorLayout();
    for (std::shared_ptr<Group> group : m_groups_collection->getCollectionRef())
    {
        addGroupItemToList(group);
    }
}

void MainWindow::setHeaderLabelText() 
{
    QString text = QString::fromStdString("Welcome To Kohot"); 
    m_header_label->setText(text);
}

void MainWindow::setListViewerLabelText()
{
    m_list_viewer_label->setText("Groups :");
}

void MainWindow::createButtonsHorLayout()
{
    m_buttons_hor_layout->addStretch(1);
    m_buttons_hor_layout->addWidget(m_create_new_group_button, 2);
    connect(m_create_new_group_button, &QPushButton::clicked, this, &MainWindow::onCreateNewGroupButton);
    m_buttons_hor_layout->addStretch(1);
}

void MainWindow::addGroupItemToList(std::shared_ptr<Group> group)
{
    GroupItemWidget * group_item_widget = new GroupItemWidget(group,this);
    QListWidgetItem *item = new QListWidgetItem(m_list_viewer_widget);
    item->setSizeHint(group_item_widget->sizeHint());
    m_list_viewer_widget->setItemWidget(item, group_item_widget);
}

// Slots : 

void MainWindow::onCreateNewGroupButton()
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

void MainWindow::onRemoveGroupButton(size_t id)
{
    m_groups_collection->deleteItem(id);
    QListWidgetItem *itemToRemove = m_list_viewer_widget->takeItem(id);
    delete itemToRemove;
    for (size_t index = id; index <  m_groups_collection->getSize(); index++)
    {
        m_groups_collection->getItem(index)->setId(static_cast<uint16_t>(index));
    }
}

void MainWindow::onEnterGroupButton(size_t id)
{
    std::shared_ptr<Group> group = m_groups_collection->getItem(id);
    GroupMenuWindow *m_group_menu_window = new GroupMenuWindow(this,group);
    m_group_menu_window->init();
    hide();
    m_group_menu_window->show();
}