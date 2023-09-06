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
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    QWidget *mainWindowWidget = new QWidget(this);
    QVBoxLayout *mainLayout = createMainLayout();
    mainWindowWidget->setLayout(mainLayout);
    stackedWidget->addWidget(mainWindowWidget);


    GroupMenuWindow *secondWindowWidget = new GroupMenuWindow(this);
    stackedWidget->addWidget(secondWindowWidget);
}

QVBoxLayout *MainWindow::createGroupsLayout()
{
    QVBoxLayout *groupsLayout = new QVBoxLayout;

    // Create a QLabel for "Groups:"
    QLabel *groupsLabel = new QLabel("Groups :", this);
    groupsLayout->addWidget(groupsLabel);

    // Create a QListWidget to hold the list of groups
    groupsLayout->addWidget(m_groupsListWidget);

    createGroupListWidget();

    return groupsLayout;
}

QVBoxLayout *MainWindow::createMainLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Create the welcome label
    QLabel *welcomeLabel = createWelcomeLabel();
    mainLayout->addWidget(welcomeLabel);

    // Create the groups layout (Groups: label and QListWidget)
    QVBoxLayout *groupsLayout = createGroupsLayout();
    mainLayout->addLayout(groupsLayout);

    // Create an horizontal layout for the button section (4 horizontal layouts)
    QHBoxLayout *buttonSectionLayout = createButtonSectionLayout();
    mainLayout->addLayout(buttonSectionLayout);

    return mainLayout;
}

MainWindow::~MainWindow()
{
    // delete ui;
}

QLabel *MainWindow::createWelcomeLabel()
{
    const QString WELCOME_TEXT = "Welcome to kohot";
    QLabel *welcomeLabel = new QLabel(WELCOME_TEXT, this);
    welcomeLabel->setAlignment(Qt::AlignHCenter);
    welcomeLabel->setFont(QFont("Arial", 24, QFont::Bold));
    return welcomeLabel;
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
     stackedWidget->setCurrentIndex(1);
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




