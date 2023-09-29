#ifndef FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include "app_common.hpp"



class DisplayTeamsWindow : public QWidget
{
    Q_OBJECT

public : 
    QHBoxLayout * m_layout = new QHBoxLayout;



};

#endif // FIRST_QT_APP_INCLUDE_DISPLAY_TEAMS_WINDOW_H