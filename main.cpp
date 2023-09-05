#include "include/mainwindow.h"

#include <QApplication>

#include "kohot.hpp"

int main(int argc, char *argv[])
{
    Kohot m_kohot;
    m_kohot.loadGroups();
    std::shared_ptr<GroupsCollection> groups_collection = m_kohot.getGroupsCollection();

    QApplication a(argc, argv);

    MainWindow main_window(nullptr,groups_collection);
    QObject::connect(&main_window, &QObject::destroyed, [&]() {
    m_kohot.saveGroups();});


    main_window.show();
    

    return a.exec();
}
