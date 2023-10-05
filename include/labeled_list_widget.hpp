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

    void addSpacerAboveList(QSpacerItem *spacer)
    {
        m_top_labels_layout->addSpacerItem(spacer);
    }

    void addLabelAboveList(const QString &text,Qt::Alignment allignment)
    {
        QLabel *label = new QLabel(text);
        label->setFont(Fonts::LIST_LABEL_FONT);
        label->setAlignment(allignment);
        m_top_labels_layout->addWidget(label);
    }

    void addLabelAboveList(QLabel *label,Qt::Alignment allignment)
    {
        label->setFont(Fonts::LIST_LABEL_FONT);
        label->setAlignment(allignment);
        m_top_labels_layout->addWidget(label);
    }

    void addLabelbeneathList(const QString &text,Qt::Alignment allignment)
    {
        QLabel *label = new QLabel(text);
        label->setFont(Fonts::LIST_LABEL_FONT);
        label->setAlignment(allignment);
        m_bottom_labels_layout->addWidget(label);
    }

    void setListColor(const QString style_sheet)
    {
       m_list->setStyleSheet(style_sheet);
    }

// UNUSED
    void addWidgetToBottom(QWidget *widget)
    {
       m_labeled_list_layout->addWidget(widget);
    }
    void addLayoutToBottom(QLayout *layout)
    {
       m_labeled_list_layout->addLayout(layout);
    }
// UNUSED


    template <typename T>
    void addItemToList(const T &custom_item)
    {
        QListWidgetItem *item = new QListWidgetItem(m_list);
        item->setSizeHint(custom_item->sizeHint());
        m_list->setItemWidget(item, custom_item);
    }


private:
    QVBoxLayout *m_labeled_list_layout;

    // QListWidget *m_list;
    QHBoxLayout *m_top_labels_layout;
    QHBoxLayout *m_bottom_labels_layout;


    void initLabeledListLayout()
    {
        m_labeled_list_layout = new QVBoxLayout(this);

        m_top_labels_layout = new QHBoxLayout;
        m_list = new QListWidget;
        m_bottom_labels_layout = new QHBoxLayout;

        m_labeled_list_layout->addLayout(m_top_labels_layout);
        m_labeled_list_layout->addWidget(m_list);
        m_labeled_list_layout->addLayout(m_bottom_labels_layout);

    }
};

#endif //FIRST_QT_APP_INCLUDE_LABELED_LIST_WIDGET_H