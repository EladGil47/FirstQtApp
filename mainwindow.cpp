#include "mainwindow.h"
#include "QtFiles/ui_mainwindow.h"


#include "kohot.hpp"

#include <QLabel>
#include <QVBoxLayout>
#include "groups_manager_menu.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

    m_kohot.loadGroups();
    std::shared_ptr<GroupsCollection> groups_collection = m_kohot.getGroupsCollection();

	// GroupsManagerMenu groups_manager_menu();

    // Set the main window properties
    setWindowTitle("Kohot");
    resize(800, 400);

    // Create a central widget to hold your layout
    QWidget *   centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the main layout for the central widget
    QVBoxLayout *mainLayout = createMainLayout();
    // Add the main layout to the central widget
    centralWidget->setLayout(mainLayout);
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
    m_kohot.saveGroups();
    delete ui;
}

QLabel *MainWindow::createWelcomeLabel()
{
    const QString WELCOME_TEXT = "Welcome to kohot";
    QLabel *welcomeLabel = new QLabel(WELCOME_TEXT, this);
    welcomeLabel->setAlignment(Qt::AlignHCenter);
    welcomeLabel->setFont(QFont("Arial", 24, QFont::Bold));
    return welcomeLabel;
}
