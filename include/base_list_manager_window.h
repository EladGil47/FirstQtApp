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
    void createWindowLayout() ;
    QVBoxLayout *m_window_layout;

    void createHeaderLabel();
    void setListViewerListWidget();
    void createListLabel();
    void setListViewerVerLayout();
    QVBoxLayout *m_list_viewer_ver_layout;

protected :
    QMainWindow *m_parent ;

    BaseListManagerWindow(QMainWindow *parent = nullptr);
    ~BaseListManagerWindow();

    virtual void initList()  = 0;
    virtual void updateList() ;

    void setHeaderLabelText(const QString &text) ;
    void setHeaderLabelEditability(bool state) ;
    EditableLabel *m_header_label ;

    virtual void setListLabelText() = 0;
    QLabel *m_list_label;
    QListWidget *m_list_viewer_widget;

    virtual void createButtonsHorLayout() = 0;
    QHBoxLayout *m_buttons_hor_layout;

    void removeAllItemsFromList() ;

};
#endif // FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H