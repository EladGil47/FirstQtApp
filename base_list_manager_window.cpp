#include "mainwindow.h"

#include <QInputDialog>
#include <QFont>
#include <QPushButton>

#include "base_list_manager_window.h"

BaseListManagerWindow::BaseListManagerWindow(QWidget *parent): QMainWindow(parent)
{
    setWindowTitle(WINDOW_TITLE);
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    createWindowWidget();
}

BaseListManagerWindow::~BaseListManagerWindow()
{
}

void BaseListManagerWindow::createWindowWidget()
{
    setCentralWidget(m_window_widget);
    createWindowLayout();
    m_window_widget->setLayout(m_window_layout);
}

void BaseListManagerWindow::createWindowLayout()
{
    setHeaderLabelCommons();
    m_window_layout->addWidget(m_header_label);
    createListViewerVerLayout();
    m_window_layout->addLayout(m_list_viewer_ver_layout);
    m_window_layout->addLayout(m_buttons_hor_layout);
}

void BaseListManagerWindow::setHeaderLabelCommons()
{
    m_header_label->setAlignment(Qt::AlignHCenter);
    m_header_label->setFont(QFont("Arial", 24, QFont::Bold));
}

void BaseListManagerWindow::createListViewerVerLayout()
{
    m_list_viewer_ver_layout->addWidget(m_list_viewer_label);
    m_list_viewer_ver_layout->addWidget(m_list_viewer_widget);
}