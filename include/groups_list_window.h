#ifndef FIRST_QT_APP_INCLUDE_MAINWINDOW_H
#define FIRST_QT_APP_INCLUDE_MAINWINDOW_H

#include <QPushButton>

#include "groups_collection.hpp"
#include "base_list_manager_window.h"

class GroupsListWindow : public BaseListManagerWindow
{
    Q_OBJECT

public:
    GroupsListWindow(std::shared_ptr<GroupsCollection> groups_collection = nullptr);
    ~GroupsListWindow();
    void changeGroupName(uint16_t id, const std::string &name);

private:
    void setListLabelText() override;
    void createButtonsHorLayout() override;

    void initGroupsAmountLabel();
    void setGroupsAmountLabelText();

    void addGroupItemToList(std::shared_ptr<Group> group);

    void initCreateNewGroupButton();
    QPushButton *m_create_new_group_button;

    std::shared_ptr<GroupsCollection> m_groups_collection;

    QLabel *m_groups_amount_label;

    void initList() override;

public slots:
    void onCreateNewGroupButton();
    void onRemoveGroupButton(size_t id);
    void onEnterGroupButton(size_t id);

signals:
    void setToPlayersListWindowSignal(size_t id);
};
#endif // FIRST_QT_APP_INCLUDE_MAINWINDOW_H