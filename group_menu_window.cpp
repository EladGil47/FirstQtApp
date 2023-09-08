#include "group_menu_window.h"

#include <QDebug>
#include <QPushButton>


void GroupMenuWindow::init() 
{
    setHeaderLabelText();
    setListViewerLabelText();
    createButtonsHorLayout();
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
    m_buttons_hor_layout->addWidget(create_new_player_button, 2);
    connect(create_new_player_button, &QPushButton::clicked, this, &GroupMenuWindow::onCreateNewPlayerButton);
    m_buttons_hor_layout->addStretch(1);
}

void GroupMenuWindow::onCreateNewPlayerButton()
{
    qDebug() << " Create player window";
}
