#ifndef FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include "app_common.hpp"

#include "base_list_manager_window.h"


class DisplayTeamsWindow : public BaseListManagerWindow
{
    Q_OBJECT

public : 
DisplayTeamsWindow()
{
    initBaseWindowLayout();
    QListWidget * sss = new QListWidget;
    m_list_list_layout->addWidget(sss);
}


};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H