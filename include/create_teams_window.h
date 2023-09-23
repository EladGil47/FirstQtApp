#ifndef FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H

#include <QWidget>
#include "base_list_manager_window.h"
#include "group.hpp"
#include <memory>




class CreateTeamsWindow : public BaseListManagerWindow
{
    Q_OBJECT

public:
    CreateTeamsWindow(std::shared_ptr<Group> group = nullptr,QMainWindow *parent = nullptr) :  BaseListManagerWindow(parent)
    {
        setHeaderLabelText(QString::fromStdString(group->getName()));
        m_list_label->setText("Players :");


    }
    void initList() override
    {

    }
    void setListLabelText() override
    {

    }
    void createButtonsHorLayout() override
    {

    }
};



#endif // FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H