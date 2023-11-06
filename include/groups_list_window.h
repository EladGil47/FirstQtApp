#ifndef FIRST_QT_APP_INCLUDE_MAINWINDOW_H
#define FIRST_QT_APP_INCLUDE_MAINWINDOW_H

#include <QPushButton>
#include <QWidget>

#include "groups_collection.hpp"
#include "labeled_list_widget.hpp"

class GroupsListWindow : public QWidget
{
    Q_OBJECT

public:
    GroupsListWindow(std::shared_ptr<GroupsCollection> groups_collection);
    ~GroupsListWindow();
    void changeGroupName(uint16_t id, const std::string& name);

private:
    void initGroupsAmountLabel();
    void setGroupsAmountLabelText();
    void addGroupItemToList(std::shared_ptr<Group> group);
    void initCreateNewGroupButton();
    void initList();
    void initAppNameLabel();
    void initGroupsList();
    void setupLayout();
    void initButtonsHorLayout();
    void initGroupsAmountLabelText();

    std::shared_ptr<GroupsCollection> m_groups_collection;

    QPushButton*       m_create_new_group_button;
    QLabel*            m_groups_amount_label;
    QLabel*            m_app_name_label;
    LabeledListWidget* m_groups_list;
    QHBoxLayout*       m_buttons_hor_layout;

public slots:
    void onCreateNewGroupButton();
    void onRemoveGroupButton(size_t id);
    void onEnterGroupButton(size_t id);
    void onCreateTeamsButton(size_t id);

signals:
    void setToPlayersListWindowSignal(size_t id);
    void setToCreateTeamsWindowSignal(size_t id);
};
#endif // FIRST_QT_APP_INCLUDE_MAINWINDOW_H