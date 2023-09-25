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
  
    Functions::checkNotNull(m_list_label,"m_list_label");
    m_list_label_layout->addWidget(m_list_label);

    m_list_layout->addLayout(m_list_label_layout);


    Functions::checkNotNull(m_list_list_widget,"m_list_list_widget");
    m_list_layout->addWidget(m_list_list_widget);
}

void BaseListManagerWindow::initListListWidget()
{
    m_list_list_widget = new QListWidget;
    // QPixmap background_image("Data/field.jpg");
    // QPixmap scaledBackground = background_image.scaled(m_list_list_widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // QPalette palette;
    // palette.setBrush(QPalette::Base, scaledBackground);
    // m_list_list_widget->setPalette(palette);
    m_list_list_widget->setStyleSheet(
        "QListWidget {"
        "border: 1px solid black;"
        "background-color : rgb(139, 69, 30);"
        "}"
        "QListWidget::item {"
        "   border: 1px solid black;"
        "}"
        "QListWidget::item:selected {"
        " background: rgba(0, 0, 255, 10%);"
        " } "
        );
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
    for (int i = 0; i < item_count; ++i)
    {
        QListWidgetItem *item = m_list_list_widget->item(0); // Get the first item
        QWidget *widget = m_list_list_widget->itemWidget(item);
        m_list_list_widget->removeItemWidget(item); // Remove the widget from the item
        delete item;                                  // Delete the item
        delete widget;                                // Delete the widget
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