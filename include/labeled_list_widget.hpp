#ifndef FIRST_QT_APP_INCLUDE_LABELED_LIST_WIDGET_H
#define FIRST_QT_APP_INCLUDE_LABELED_LIST_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>

#include "app_common.hpp"


class LabeledListWidget : public QWidget
{
    Q_OBJECT

public:
    QListWidget *m_list;

    LabeledListWidget() 
    {
        initLabeledListLayout();
    }

    void addLabel(const QString &text,Qt::Alignment allignment)
    {
        QLabel *label = new QLabel(text);
        label->setFont(Fonts::LIST_LABEL_FONT);
        label->setAlignment(allignment);
        m_labels_layout->addWidget(label);
    }

    void setListColor(const QString style_sheet)
    {
       m_list->setStyleSheet(style_sheet);
    }

    void addWidget(QWidget *widget)
    {
       m_labeled_list_layout->addWidget(widget);
    }

    void addLayout(QLayout *layout)
    {
       m_labeled_list_layout->addLayout(layout);
    }

    template <typename T>
    void addItemToList(const T &custom_item)
    {
        QListWidgetItem *item = new QListWidgetItem(m_list);
        item->setSizeHint(custom_item->sizeHint());
        m_list->setItemWidget(item, custom_item);

        //  QListWidgetItem *item = new QListWidgetItem(custom_item);
        // item->setSizeHint(custom_item->sizeHint());
        // m_list->setItemWidget(item, custom_item);
        // m_list->addItem(custom_item);
    }


private:
    QVBoxLayout *m_labeled_list_layout;
    QHBoxLayout *m_labels_layout;

    void initLabeledListLayout()
    {
        m_labeled_list_layout = new QVBoxLayout(this);

        m_labels_layout = new QHBoxLayout;
        m_list = new QListWidget;

        m_labeled_list_layout->addLayout(m_labels_layout);
        m_labeled_list_layout->addWidget(m_list);
    }
};

// Example usage:
// LabeledListWidget *labeledListWidget = new LabeledListWidget;
// labeledListWidget->addLabel("Label 1");
// labeledListWidget->addItemToList("Item 1");
// labeledListWidget->addItemToList(42);  // Add an integer
// labeledListWidget->addItemToList(3.14);  // Add a double
// labeledListWidget->show();

#endif //FIRST_QT_APP_INCLUDE_LABELED_LIST_WIDGET_H