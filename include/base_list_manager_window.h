#ifndef FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H
#define FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>


class BaseListManagerWindow : public QMainWindow
{
    Q_OBJECT

private:

    void createWindowWidget();
    QWidget *m_window_widget = new QWidget(this);

    void createWindowLayout() ;
    QVBoxLayout *m_window_layout = new QVBoxLayout;

    void setHeaderLabelCommons();

    void createListViewerVerLayout();
    QVBoxLayout *m_list_viewer_ver_layout = new QVBoxLayout;

    protected :
    BaseListManagerWindow(QWidget *parent = nullptr);
    ~BaseListManagerWindow();
    QWidget *m_parent ;


    virtual void init()  = 0;

    virtual void setHeaderLabelText() = 0;
    QLabel *m_header_label = new QLabel(this);

    virtual void setListViewerLabelText() = 0;
    QLabel *m_list_viewer_label = new QLabel(this);
    QListWidget *m_list_viewer_widget = new QListWidget(this);

    virtual void createButtonsHorLayout() = 0;
    QHBoxLayout *m_buttons_hor_layout = new QHBoxLayout; 

};
#endif // FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H