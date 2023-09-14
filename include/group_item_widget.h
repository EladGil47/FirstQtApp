#ifndef FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H

#include "group.hpp"
#include "groups_list_window.h"
#include "editable_label.h"


class GroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    GroupItemWidget(std::shared_ptr<Group> group= nullptr, GroupsListWindow* parent = nullptr);

private:

size_t m_group_index ; 
void setGroupIndex(size_t group_index);


void setNameLabel();
void setSizeLabel();
void setEnterButton();
void setRemoveButton();
void setItemHorLayout();

std::shared_ptr<Group> m_group;
GroupsListWindow * m_groups_list_window;

EditableLabel* m_name_label;
QLabel* m_size_label;
QPushButton* m_enter_button;
QPushButton* m_remove_button;



QHBoxLayout * m_item_hor_layout;

public slots:
void onEnterButtonClicked(bool a);
void onRemoveButtonClicked(bool a);
void onChangeGroupName(const QString& name);




};
#endif // FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H