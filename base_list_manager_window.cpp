#include "base_list_manager_window.h"
#include "app_common.hpp"

BaseListManagerWindow::BaseListManagerWindow()
{
    initHeaderLabel();
    initListLabel();
    initListListWidget();
    initListLayout();
    m_buttons_hor_layout = new QHBoxLayout;
}

BaseListManagerWindow::~BaseListManagerWindow()
{
    delete m_header_label;
    delete m_list_label;
    removeAllItemsFromList();
    delete m_list_list_widget;
    delete m_list_layout;
    delete m_buttons_hor_layout;
    delete m_window_layout;
}

void BaseListManagerWindow::initHeaderLabel()
{
    m_header_label = new EditableLabel;
    m_header_label->setFont(Fonts::HEADER_LABEL_FONT);
    m_header_label->setAlignment(Qt::AlignHCenter);
}

void BaseListManagerWindow::initListLabel()
{
    m_list_label = new QLabel;
    m_list_label->setFont(Fonts::LIST_LABEL_FONT);
}

void BaseListManagerWindow::initListLayout()
{
    m_list_layout = new QVBoxLayout;

    m_list_label_layout = new QHBoxLayout;
    m_list_list_layout = new QHBoxLayout;

  
    Functions::checkNotNull(m_list_label,"m_list_label");
    m_list_label_layout->addWidget(m_list_label);

    m_list_layout->addLayout(m_list_label_layout);


    Functions::checkNotNull(m_list_list_widget,"m_list_list_widget");
    m_list_list_layout->addWidget(m_list_list_widget);

    m_list_layout->addLayout(m_list_list_layout);

}

void BaseListManagerWindow::initListListWidget()
{
    m_list_list_widget = new QListWidget;
    m_list_list_widget->setStyleSheet(Style::LIST);
}

void BaseListManagerWindow::initBaseWindowLayout()
{
    Functions::checkNotNull(m_header_label,"m_header_label");
    m_window_layout->addWidget(m_header_label);
    Functions::checkNotNull(m_list_layout,"m_list_layout");
    m_window_layout->addLayout(m_list_layout);
    Functions::checkNotNull(m_buttons_hor_layout,"m_buttons_hor_layout");
    m_window_layout->addLayout(m_buttons_hor_layout);
}

void BaseListManagerWindow::removeAllItemsFromList()
{
    int item_count = m_list_list_widget->count();
    int const FIRST_ROW =  0;
    for (int i = FIRST_ROW; i < item_count; ++i)
    {   
        // Each iteration the first elemnt is deleted which means second element becoming first
        QListWidgetItem *item = m_list_list_widget->item(FIRST_ROW); 
        QWidget *widget = m_list_list_widget->itemWidget(item);
        m_list_list_widget->removeItemWidget(item);
        delete item;                                 
        delete widget;                            
    }
}

void BaseListManagerWindow::updateList()
{
    removeAllItemsFromList();
    initList();
}

void BaseListManagerWindow::setHeaderLabelText(const QString &text) 
{
    m_header_label->setText(text);
}

void BaseListManagerWindow::setHeaderLabelEditability(bool state) 
{
    m_header_label->setEditablity(state);
}