#include "mainwindow.h"

#include <QInputDialog>
#include <QFont>

#include "group_item_widget.h"

MainWindow::MainWindow(std::shared_ptr<GroupsCollection> groups_collection,QMainWindow *parent):
BaseListManagerWindow(parent),
m_groups_collection(groups_collection)
{
    init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init() 
{
    setHeaderLabelText(QString::fromStdString("Welcome To Kohot"));
    setHeaderLabelEditability(false);
    setListViewerLabelText();
    setCreateNewGroupButton();
    createButtonsHorLayout();
    initList();
}

void MainWindow::setCreateNewGroupButton()
{
    QString text = "Create new group";
    m_create_new_group_button = new QPushButton(text, this);
    m_create_new_group_button->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"     // Green background color
        "    border: 2px solid #4CAF50;"     // Green border
        "    color: white;"                  // White text color
        "    padding: 10px 20px;"            // Padding around the text
        "    font-size: 18px;"              // Font size
        "    font-weight: bold;"            // Bold text
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"    // Darker green on hover
        "    border: 2px solid #45a049;"    // Darker green border on hover
        "}"
    );
    // Set the button's size policy (optional)
    m_create_new_group_button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_create_new_group_button->setToolTip("Click here to create a new group");
    connect(m_create_new_group_button, &QPushButton::clicked, this, &MainWindow::onCreateNewGroupButton);
}

void MainWindow::initList()
{
    for (std::shared_ptr<Group> group : m_groups_collection->getCollectionRef())
    {
        addGroupItemToList(group);
    }
}



void MainWindow::setListViewerLabelText()
{
    m_list_viewer_label->setText("Groups :");
}

void MainWindow::createButtonsHorLayout()
{
    m_buttons_hor_layout->addStretch(1);
    m_buttons_hor_layout->addWidget(m_create_new_group_button, 2);
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
    QListWidgetItem *itemToRemove = m_list_viewer_widget->takeItem(id);
    delete itemToRemove;
    m_groups_collection->deleteItem(id);
    for (size_t index = id; index <  m_groups_collection->getSize(); index++)
    {
        m_groups_collection->getItem(index)->setId(static_cast<uint16_t>(index));
    }
    updateList();
}

void MainWindow::onEnterGroupButton(size_t id)
{
    emit switchToGroupMenuWidgetSignal(id);
}