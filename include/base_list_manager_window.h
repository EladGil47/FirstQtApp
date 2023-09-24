#ifndef FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H
#define FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>

#include "editable_label.h"

class BaseListManagerWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout * m_window_layout = new QVBoxLayout(this);
    void initListListWidget();
    void initListLabel();
    void initListLayout();
    QVBoxLayout *m_list_layout;
    void removeAllItemsFromList() ;
    void initHeaderLabel();

    

protected :
    BaseListManagerWindow();
    ~BaseListManagerWindow();


    void initBaseWindowLayout() ;
    virtual void initList()  = 0;
    virtual void setListLabelText() = 0;
    virtual void createButtonsHorLayout() = 0;

    void updateList() ;
    void setHeaderLabelText(const QString &text) ;
    void setHeaderLabelEditability(bool state) ;

    EditableLabel *m_header_label ;
    QLabel *m_list_label;
    QListWidget *m_list_list_widget;
    QHBoxLayout *m_buttons_hor_layout;

    QHBoxLayout *  m_list_label_layout;
};

#endif // FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H