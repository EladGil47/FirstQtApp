#include "include/mainwindow.h"

#include <QApplication>

#include "groups_manager_menu.hpp"
#include "kohot.hpp"

int main(int argc, char *argv[]) {

  int ret_val = 0;
  Kohot kohot;
  kohot.loadGroups();
  std::shared_ptr<GroupsCollection> groups_collection = kohot.getGroupsCollection();

  bool isConsoleApp = true;
  if (isConsoleApp) 
  {
    GroupsManagerMenu xxx(groups_collection);
    xxx.handle();
  }
  else 
  {
    QApplication a(argc, argv);

    MainWindow main_window(nullptr, groups_collection);
    QObject::connect(&main_window, &QObject::destroyed,
                     [&]() { kohot.saveGroups(); });
    main_window.show();

    ret_val = a.exec();
  }

  return ret_val;
}
