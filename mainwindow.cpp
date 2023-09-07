#include "mainwindow.h"

#include <QInputDialog>
#include <QFont>
#include <QPushButton>

#include "group_menu_window.h"


MainWindow::MainWindow(QWidget *parent,std::shared_ptr<GroupsCollection> groups_collection): QMainWindow(parent)
{
    m_groups_collection = groups_collection;
    setWindowTitle(WINDOW_TITLE);
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowContent();
}

MainWindow::~MainWindow()
{
}

void MainWindow::addGroupItemToList(std::shared_ptr<Group> group)
{
    QWidget *list_item_widget = new QWidget;
    QHBoxLayout *group_list_item_layout = new QHBoxLayout(list_item_widget);

    // Create the group_name label
    QString group_name = QString::fromStdString(group->getName());
    QLabel *group_name_label = new QLabel(group_name, this);
    group_name_label->setAlignment(Qt::AlignLeft);
    group_name_label->setFont(QFont("Arial", 16, QFont::Bold));
    group_list_item_layout->addWidget(group_name_label);

    // Create the enter group button
    QPushButton *enter_group_button = new QPushButton("Enter");
    enter_group_button->setStyleSheet("text-align: center;"
                                      "background-color: green;");
    group_list_item_layout->addWidget(enter_group_button);
    connect(enter_group_button, &QPushButton::clicked, this, [=]()
            { onEnterGroupButton(group->getId()); });

    group_list_item_layout->addSpacing(1);

    // Create the remove group button
    QPushButton *remove_group_button = new QPushButton("Remove");
    remove_group_button->setStyleSheet("text-align: center;"
                                       "background-color: red;");
    group_list_item_layout->addWidget(remove_group_button);
    connect(remove_group_button, &QPushButton::clicked, this, [=]()
            { onRemoveGroupButton(group->getId()); });

    QListWidgetItem *item = new QListWidgetItem(m_groups_list_widget);
    item->setSizeHint(list_item_widget->sizeHint());
    m_groups_list_widget->setItemWidget(item, list_item_widget);
}

void MainWindow::setWindowContent()
{
    setCentralWidget(m_main_window_widget);
    createMainLayout();
    m_main_window_widget->setLayout(m_main_window_layout);
}

void MainWindow::createGroupsVerLayout()
{
    m_groups_ver_layout->addWidget(m_groups_label);
    m_groups_ver_layout->addWidget(m_groups_list_widget);
    for (std::shared_ptr<Group> group : m_groups_collection->getCollectionRef())
    {
        addGroupItemToList(group);
    }
}

void MainWindow::createMainLayout()
{
    createWelcomeLabel();
    m_main_window_layout->addWidget(m_welcome_label);
    createGroupsVerLayout();
    m_main_window_layout->addLayout(m_groups_ver_layout);
    createButtonHorLayout();
    m_main_window_layout->addLayout(m_button_hor_layout);
}

void MainWindow::createWelcomeLabel()
{
    m_welcome_label->setAlignment(Qt::AlignHCenter);
    m_welcome_label->setFont(QFont("Arial", 24, QFont::Bold));
}

void MainWindow::createButtonHorLayout()
{
    m_button_hor_layout->addStretch(1);
    QPushButton *create_new_group_button = new QPushButton("Create new group",this);
    m_button_hor_layout->addWidget(create_new_group_button, 2);
    connect(create_new_group_button, &QPushButton::clicked, this, &MainWindow::onCreateGroupButton);
    m_button_hor_layout->addStretch(1);
}

void MainWindow::onCreateGroupButton()
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
    QListWidgetItem *itemToRemove = m_groups_list_widget->takeItem(id);
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
    m_group_menu_window->show();
}