#include <QApplication>

#include "groups_manager_menu.hpp"
#include "kohot.hpp"

#include "custom_window.h"



int main(int argc, char *argv[]) {

  int ret_val = 0;
  Kohot kohot;
  kohot.loadGroups();
  std::shared_ptr<GroupsCollection> groups_collection = kohot.getGroupsCollection();

  bool isConsoleApp = false;
  if (isConsoleApp) 
  {
    GroupsManagerMenu groups_manager_menu(groups_collection);
    ret_val = groups_manager_menu.handle() ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else 
  {
    QApplication a(argc, argv);
    CustomWindow window(groups_collection);
    QObject::connect(&window, &QObject::destroyed,[&kohot]()
    {
      kohot.saveGroups();
    } ) ;
    // This is How to switch QWidget on window
    // QWidget * ss = new QWidget(&window);
    // window.setCentralWidget(ss);
    ret_val = a.exec();
  }

  return ret_val;
}
