#include "mainwindow.h"

#include <QInputDialog>
#include <QFont>

#include "group_menu_window.h"

MainWindow::MainWindow(QWidget *parent,std::shared_ptr<GroupsCollection> groups_collection):BaseListManagerWindow(parent)
{
    m_groups_collection = groups_collection;
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
    QWidget *list_item_widget = new QWidget;
    list_item_widget->setStyleSheet("QWidget { border: 2px solid black; }");

    QHBoxLayout *group_list_item_layout = new QHBoxLayout(list_item_widget);

    // Create the group_name label
    QString group_name = QString::fromStdString(group->getName());
    QLabel *group_name_label = new QLabel(group_name, list_item_widget);
    group_name_label->setFont(QFont("Arial", 16, QFont::Bold));
    group_name_label->setStyleSheet("border: none;");
    group_name_label->setAlignment(Qt::AlignLeft);



    // Create the group_size label
    QString group_size = QString::number(group->getNumOfPlayers());
    QString group_size_wrapped = "(" +  group_size + ")";
    QLabel *group_size_label = new QLabel(group_size_wrapped, list_item_widget);
    group_size_label->setFont(QFont("Arial", 16, QFont::Bold));
    group_size_label->setStyleSheet("border: none;");
    group_size_label->setAlignment(Qt::AlignLeft);



    size_t group_id = group->getId();

    // Create the enter group button
    QPushButton *enter_button = new QPushButton("Enter",list_item_widget);
    enter_button->setStyleSheet("text-align: center;""background-color: green;" "border: none;");
    connect(enter_button, &QPushButton::clicked, this, [=]()
            { onEnterGroupButton(group_id); });
            

    // Create the remove group button
    QPushButton *remove_button = new QPushButton("Remove",list_item_widget);
    remove_button->setStyleSheet("text-align: center;" "background-color: red;""border: none;");
    connect(remove_button, &QPushButton::clicked, this, [=]()
            { onRemoveGroupButton(group_id); });


    // Add created widgets to layout
    group_list_item_layout->addWidget(group_name_label,1);
    group_list_item_layout->addWidget(group_size_label,4);
    group_list_item_layout->addWidget(enter_button,1);
    group_list_item_layout->addWidget(remove_button,1);


    QListWidgetItem *item = new QListWidgetItem(m_list_viewer_widget);
    item->setSizeHint(list_item_widget->sizeHint());
    m_list_viewer_widget->setItemWidget(item, list_item_widget);
}

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
    hide();
    std::shared_ptr<Group> group = m_groups_collection->getItem(id);
    GroupMenuWindow *m_group_menu_window = new GroupMenuWindow(this,group);
    m_group_menu_window->init();
    // m_group_menu_window->setHeaderLabelText();
    m_group_menu_window->show();

    // BaseListManagerWindow *m_group_menu_window = new BaseListManagerWindow(this);
    // m_group_menu_window->show();

    
}