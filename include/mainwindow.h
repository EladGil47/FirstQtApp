#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QListWidget>

#include <vector>
#include <string>
#include "groups_collection.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,std::shared_ptr<GroupsCollection> groups_collection = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *createMainLayout();
    QLabel *createWelcomeLabel();
    QVBoxLayout *createGroupsLayout();
    QHBoxLayout *createButtonSectionLayout();
    void createGroupListWidget();

    void addGroupItemToList(std::shared_ptr<Group> group);


    QListWidget *m_groupsListWidget = new QListWidget(this);


    void setWindowContent();
    std::shared_ptr<GroupsCollection> m_groups_collection;

public slots:
    void onCreateGroupButton();
    void onRemoveGroupButton(size_t id);
    void onEnterGroupButton(size_t id);
};
#endif // MAINWINDOW_H
