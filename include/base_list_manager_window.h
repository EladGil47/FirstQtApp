#ifndef FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H
#define FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>


#include <vector>
#include <memory>




class BaseListManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    BaseListManagerWindow(QWidget *parent = nullptr);
    ~BaseListManagerWindow();
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 400;
    const QString WINDOW_TITLE = "Kohot";

private:
    QWidget *m_main_window_widget = new QWidget(this);

    void createMainLayout() ;
    QVBoxLayout *m_main_window_layout = new QVBoxLayout;

    void setHeaderLabelCommons();

    void createListViewerVerLayout();
    QVBoxLayout *m_list_viewer_ver_layout = new QVBoxLayout;
    QListWidget *m_list_viewer_widget = new QListWidget(this);





    // void createButtonsHorLayout();


    // void addGroupItemToList(std::shared_ptr<Group> group);



    // std::shared_ptr<GroupsCollection> m_groups_collection;

    void setWindowContent();

    protected :
    virtual void setHeaderLabelText() = 0;
    QLabel *m_header_label = new QLabel(this);

    virtual void setListViewerLabelText() = 0;
    QLabel *m_list_viewer_label = new QLabel(this);

    virtual void createButtonsHorLayout() = 0;
    QHBoxLayout *m_buttons_hor_layout = new QHBoxLayout; 



    // std::shared_ptr<std::vector<QPushButton *>> m_buttons = std::make_shared<std::vector<QPushButton*>>();



    virtual void init()  = 0;







// public slots:
    // void onCreateGroupButton();
    // void onRemoveGroupButton(size_t id);
    // void onEnterGroupButton(size_t id);

};
#endif // FIRST_QT_APP_INCLUDE_BASE_LIST_MANAGER_WINDOW_H