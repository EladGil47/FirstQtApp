#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>

#include "groups_collection.hpp"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,std::shared_ptr<GroupsCollection> groups_collection = nullptr);
    ~MainWindow();

private:
    void setWindowContent();
    void createMainLayout();
    void createWelcomeLabel();
    void createGroupsVerLayout();
    void createButtonHorLayout();
    void addGroupItemToList(std::shared_ptr<Group> group);

    QWidget *m_main_window_widget = new QWidget(this);
    QVBoxLayout *m_main_layout = new QVBoxLayout;
    QLabel *m_welcome_label = new QLabel("Welcome to kohot", this);
    QVBoxLayout *m_groups_ver_layout = new QVBoxLayout;
    QLabel *m_groups_label = new QLabel("Groups :", this);
    QListWidget *m_groups_list_widget = new QListWidget(this);
    QHBoxLayout *m_button_hor_layout = new QHBoxLayout;

    std::shared_ptr<GroupsCollection> m_groups_collection;

public slots:
    void onCreateGroupButton();
    void onRemoveGroupButton(size_t id);
    void onEnterGroupButton(size_t id);
};
#endif // MAINWINDOW_H