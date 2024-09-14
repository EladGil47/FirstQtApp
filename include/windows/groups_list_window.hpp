#ifndef FIRST_QT_APP_INCLUDE_MAINWINDOW_H
#define FIRST_QT_APP_INCLUDE_MAINWINDOW_H

#include <QPushButton>
#include <QWidget>

#include "groups_collection.hpp"
#include "labeled_list_widget.hpp"

#include "editable_label.hpp"

class GroupsListWindow : public QWidget
{
    Q_OBJECT

public:
    GroupsListWindow(std::shared_ptr<GroupsCollection> groups_collection);
    ~GroupsListWindow();
    void changeGroupName(uint16_t id, const std::string& name);

private:
    static constexpr const char* CREATE_NEW_GROUP_BUTTON_TEXT = "Create new group";

    void initGroupsAmountLabel();
    void updateGroupsAmountLabel();
    void addGroupItemToList(std::shared_ptr<Group> group);
    void initCreateNewGroupButton();
    void initList();
    void initAppNameLabel();
    void initGroupsList();
    void setupLayout();
    void setupButtonsHorLayout();
    void initAppHorLayout();

    std::shared_ptr<GroupsCollection>  m_groups_collection;
    std::unique_ptr<QHBoxLayout>       m_app_name_hor_layout;
    std::unique_ptr<LabeledListWidget> m_groups_list;
    std::unique_ptr<QPushButton>       m_create_new_group_button;
    std::unique_ptr<QHBoxLayout>       m_buttons_hor_layout;

    std::unique_ptr<EditableLabel> m_app_name_label;

    std::unique_ptr<QLabel> m_groups_amount_label;

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