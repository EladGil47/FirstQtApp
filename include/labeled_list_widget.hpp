#ifndef FIRST_QT_APP_INCLUDE_LABELED_LIST_WIDGET_H
#define FIRST_QT_APP_INCLUDE_LABELED_LIST_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>

class LabeledListWidget : public QWidget
{
    Q_OBJECT

public:
    LabeledListWidget() 
    {
        initLabeledListLayout();
    }

    void addLabel(const QString &text)
    {
        QLabel *label = new QLabel(text);
        m_labels_layout->addWidget(label);
    }

    template <typename T>
    void addItemToList(const T &custom_item)
    {
        QListWidgetItem *item = new QListWidgetItem(m_list);
        item->setSizeHint(custom_item->sizeHint());
        m_list->setItemWidget(item, custom_item);
    }

private:
    QVBoxLayout *m_labeled_list_layout;
    QHBoxLayout *m_labels_layout;
    QListWidget *m_list;

    void initLabeledListLayout()
    {
        m_labeled_list_layout = new QVBoxLayout(this);
        m_labels_layout = new QHBoxLayout;
        m_list = new QListWidget;

        m_labeled_list_layout->addLayout(m_labels_layout);
        m_labeled_list_layout->addWidget(m_list);

        // Add labels and other initialization as needed...
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