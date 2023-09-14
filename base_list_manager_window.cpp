#include "base_list_manager_window.h"

#include "editable_label.h"
#include "app_common.hpp"

BaseListManagerWindow::BaseListManagerWindow(QMainWindow *parent): QWidget(parent)
{
    m_parent = parent;
    setHeaderLabelCommons();
    setListViewerLabel();
    setListViewerListWidget();
    setListViewerVerLayout();
    setWindowLayout();
}

BaseListManagerWindow::~BaseListManagerWindow()
{
}


void BaseListManagerWindow::setHeaderLabelCommons()
{
    m_header_label = new EditableLabel(this);
    m_header_label->setFont(QFont(Common::FONT_FAMILY_NAME, 22, QFont::Bold));
    m_header_label->setAlignment(Qt::AlignHCenter);
}

void BaseListManagerWindow::setListViewerLabel()
{
    m_list_viewer_label = new QLabel(this);
    QString list_viewer_label_stylesheet =
    "QLabel {"
    "    color: black;"                
    "    font-size: 20px;"            
    "    font-weight: bold;"          
    "}";

    m_list_viewer_label->setStyleSheet(list_viewer_label_stylesheet);
   
}

void BaseListManagerWindow::setListViewerVerLayout()
{
    m_list_viewer_ver_layout = new QVBoxLayout;
    m_list_viewer_ver_layout->addWidget(m_list_viewer_label);
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

void BaseListManagerWindow::setWindowLayout()
{
    m_window_layout = new QVBoxLayout(this);
    m_window_layout->addWidget(m_header_label);
    m_window_layout->addLayout(m_list_viewer_ver_layout);
    m_window_layout->addLayout(m_buttons_hor_layout);
    setLayout(m_window_layout);

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
    m_header_label->getLabel()->setText(text);
}

void BaseListManagerWindow::setHeaderLabelEditability(bool state) 
{
    m_header_label->setEditablity(state);
}