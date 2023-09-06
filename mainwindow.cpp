#include "mainwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QInputDialog>

#include "group_menu_window.h"

MainWindow::MainWindow(QWidget *parent,std::shared_ptr<GroupsCollection> groups_collection): QMainWindow(parent)
{
    m_groups_collection = groups_collection;
    setWindowTitle("Kohot");
    resize(800, 400);
    setWindowContent();
}
void MainWindow::addGroupItemToList(std::shared_ptr<Group> group)
{
    QWidget *listItemWidget = new QWidget;
    QHBoxLayout *listItemLayout = new QHBoxLayout(listItemWidget);

    // Create the group label
    QString group_name =  QString::fromStdString(group->getName());
    QLabel *group_name_label = new QLabel(group_name, this);
    group_name_label->setAlignment(Qt::AlignLeft);
    group_name_label->setFont(QFont("Arial", 16, QFont::Bold));
    listItemLayout->addWidget(group_name_label);

    // Create the enter group button
    QPushButton *enter_group_button = new QPushButton("Enter");
    enter_group_button->setStyleSheet("text-align: center;"
                                "background-color: green;");
    listItemLayout->addWidget(enter_group_button);
    connect(enter_group_button, &QPushButton::clicked, this, [=]() {
     onEnterGroupButton(group->getId());
});


    listItemLayout->addSpacing(1);

    // Create the remove group button
    QPushButton *remove_group_button = new QPushButton("Remove");
    remove_group_button->setStyleSheet("text-align: center;""background-color: red;");
    listItemLayout->addWidget(remove_group_button);
    connect(remove_group_button, &QPushButton::clicked, this, [=]() {
    onRemoveGroupButton(group->getId());
});

    QListWidgetItem *item = new QListWidgetItem(m_groupsListWidget);
    // m_groupsListWidget->addItem(item);
    item->setSizeHint(listItemWidget->sizeHint());
    m_groupsListWidget->setItemWidget(item, listItemWidget);

}

void MainWindow::createGroupListWidget()
{
    for (std::shared_ptr<Group> group : m_groups_collection->getCollectionRef())
    {
        addGroupItemToList(group);
    }
}

void MainWindow::setWindowContent()
{
    setCentralWidget(m_stacked_widget);
    createMainLayout();
    m_main_window_widget->setLayout(m_main_layout);
    m_stacked_widget->addWidget(m_main_window_widget);

    // GroupMenuWindow *secondWindowWidget = new GroupMenuWindow(this);
    // m_stacked_widget->addWidget(secondWindowWidget);
}

void MainWindow::createGroupsVerLayout()
{
    // Create a QLabel for "Groups:"
    QLabel *groupsLabel = new QLabel("Groups :", this);
    m_groups_ver_layout->addWidget(groupsLabel);

    // Create a QListWidget to hold the list of groups
    m_groups_ver_layout->addWidget(m_groupsListWidget);

    createGroupListWidget();

}

void MainWindow::createMainLayout()
{
    createWelcomeLabel();
    m_main_layout->addWidget(m_welcome_label);

    createGroupsVerLayout();
    m_main_layout->addLayout(m_groups_ver_layout);

    QHBoxLayout *buttonSectionLayout = createButtonSectionLayout();
    m_main_layout->addLayout(buttonSectionLayout);

}

MainWindow::~MainWindow()
{
}

void MainWindow::createWelcomeLabel()
{
    m_welcome_label->setAlignment(Qt::AlignHCenter);
    m_welcome_label->setFont(QFont("Arial", 24, QFont::Bold));
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
    QListWidgetItem *itemToRemove = m_groupsListWidget->takeItem(id);
    delete itemToRemove;
    for (size_t index = id; index <  m_groups_collection->getSize(); index++)
    {
        m_groups_collection->getItem(index)->setId(static_cast<uint16_t>(index));
    }
}

void MainWindow::onEnterGroupButton(size_t id)
{
     m_stacked_widget->setCurrentIndex(1);
    // Create and open the new window (assuming MyNewWindow is the name of your new window class)
    // GroupMenuWindow *newWindow = new GroupMenuWindow;
    // newWindow->show();
    // hide();
    // close();

}

QHBoxLayout *MainWindow::createButtonSectionLayout()
{
    QHBoxLayout *buttonSectionLayout = new QHBoxLayout;

    buttonSectionLayout->addStretch(1);

    QPushButton *create_new_group_button = new QPushButton("Create new group",this);
    buttonSectionLayout->addWidget(create_new_group_button, 2);
    connect(create_new_group_button, &QPushButton::clicked, this, &MainWindow::onCreateGroupButton);
         
    buttonSectionLayout->addStretch(1);

    // QPushButton *remove_group_button = new QPushButton("Remove group",this);
    // buttonSectionLayout->addWidget(remove_group_button, 2);
    // buttonSectionLayout->addStretch(1);

    return buttonSectionLayout;
}




