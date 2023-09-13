#ifndef FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H
#define FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>

class BaseListManagerWindow : public QWidget
{
    Q_OBJECT

public: 
    QMainWindow *m_parent ;

    void setWindowWidget();

private:
    void setWindowLayout() ;
    QVBoxLayout *m_window_layout;

    void setHeaderLabelCommons();

    void setListViewerListWidget();

void setListViewerLabel();


    void setListViewerVerLayout();
    QVBoxLayout *m_list_viewer_ver_layout;

    protected :
    BaseListManagerWindow(QMainWindow *parent = nullptr);
    ~BaseListManagerWindow();

    virtual void init()  = 0;
    virtual void initList()  = 0;
    virtual void updateList() ;


    virtual void setHeaderLabelText() = 0;
    QLabel *m_header_label ;

    virtual void setListViewerLabelText() = 0;
    QLabel *m_list_viewer_label;
    QListWidget *m_list_viewer_widget;

    virtual void createButtonsHorLayout() = 0;
    QHBoxLayout *m_buttons_hor_layout = new QHBoxLayout;

    void removeAllItemsFromList() ;

};
#endif // FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H