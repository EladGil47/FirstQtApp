#include "base_list_manager_window.h"
#include "app_common.hpp"

BaseListManagerWindow::BaseListManagerWindow(QMainWindow *parent): QWidget(parent)
{
    m_parent = parent;
    createHeaderLabel();
    createListLabel();
    setListViewerListWidget();
    setListViewerVerLayout();
    createWindowLayout();
    Functions::checkNotNull(m_window_layout,"m_window_layout");
    setLayout(m_window_layout);
}

BaseListManagerWindow::~BaseListManagerWindow()
{
}


void BaseListManagerWindow::createHeaderLabel()
{
    m_header_label = new EditableLabel(this);
    m_header_label->setFont(QFont(Common::FONT_FAMILY_NAME, 22, QFont::Bold));
    m_header_label->setAlignment(Qt::AlignHCenter);
}

void BaseListManagerWindow::createListLabel()
{
    m_list_label = new QLabel(this);
    m_list_label->setFont(QFont(Common::FONT_FAMILY_NAME, 18, QFont::Bold));
}

void BaseListManagerWindow::setListViewerVerLayout()
{
    m_list_viewer_ver_layout = new QVBoxLayout;
    m_list_viewer_ver_layout->addWidget(m_list_label);
    m_list_viewer_ver_layout->addWidget(m_list_viewer_widget);
}

void BaseListManagerWindow::setListViewerListWidget()
{
    m_list_viewer_widget = new QListWidget(this);
    QPixmap background_image("Data/field.jpg");
    QPixmap scaledBackground = background_image.scaled(m_list_viewer_widget->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Base, scaledBackground);
    m_list_viewer_widget->setPalette(palette);
    m_list_viewer_widget->setStyleSheet("QListWidget {border: 3px solid black;} QListWidget::item { border: 1px solid border;} QListWidget::item:selected { background: rgba(0, 0, 255, 10%); } ");
}

void BaseListManagerWindow::createWindowLayout()
{
    m_window_layout = new QVBoxLayout(this);
    Functions::checkNotNull(m_header_label,"m_header_label");
    m_window_layout->addWidget(m_header_label);

    Functions::checkNotNull(m_list_viewer_ver_layout,"m_list_viewer_ver_layout");
    m_window_layout->addLayout(m_list_viewer_ver_layout);

    Functions::checkNotNull(m_buttons_hor_layout,"m_buttons_hor_layout");
    m_window_layout->addLayout(m_buttons_hor_layout);
}

void BaseListManagerWindow::removeAllItemsFromList()
{
    int item_count = m_list_viewer_widget->count();
    for (int i = 0; i < item_count; ++i)
    {
        QListWidgetItem *item = m_list_viewer_widget->item(0); // Get the first item
        QWidget *widget = m_list_viewer_widget->itemWidget(item);
        m_list_viewer_widget->removeItemWidget(item); // Remove the widget from the item
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