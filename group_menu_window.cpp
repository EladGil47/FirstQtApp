#include "group_menu_window.h"

#include <QString>
#include <QLabel>

#include <QMainWindow>
// #include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QInputDialog>
#include <QFont>
#include <QPushButton>


void GroupMenuWindow::setWindowContent()
{
    setCentralWidget(m_group_menu_window_widget);
    createGroupMenuLayout();
    m_group_menu_window_widget->setLayout(m_group_menu_ver_layout);
}

void GroupMenuWindow::createGroupMenuLayout()
{
    QString group_name = QString::fromStdString(m_group->getName()); 
    QLabel * group_name_label = new QLabel(group_name,this);
    group_name_label->setAlignment(Qt::AlignHCenter);
    group_name_label->setFont(QFont("Arial", 24, QFont::Bold));
    m_group_menu_ver_layout->addWidget(group_name_label);
    // createGroupsVerLayout();
    // m_main_window_layout->addLayout(m_groups_ver_layout);
    // createButtonHorLayout();
    // m_main_window_layout->addLayout(m_button_hor_layout);
}

// void GroupMenuWindow::createGroupNameLabel()
// {
//     // m_group_name_label->setAlignment(Qt::AlignHCenter);
//     m_group_name_label->setFont(QFont("Arial", 24, QFont::Bold));
// }