#ifndef GROUP_ITEM_WIDGET_H
#define GROUP_ITEM_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <memory>

#include "group.hpp"
#include "mainwindow.h"


class GroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    GroupItemWidget(std::shared_ptr<Group> group, MainWindow* parent);

private:
void setNameLabel();
void setSizeLabel();
void setEnterButton();
void setRemoveButton();
void setupLayout();


std::shared_ptr<Group> m_group;
MainWindow * m_main_window;

QLabel* m_name_label;
QLabel* m_size_label;
QPushButton* m_enter_button;
QPushButton* m_remove_button;

};
#endif // GROUP_ITEM_WIDGET_H
