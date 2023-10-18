#include <QApplication>

#include "kohot.hpp"
#include "windows_manager.h"

int main(int argc, char *argv[])
{
  int ret_val = EXIT_SUCCESS;
  Kohot kohot;
  kohot.loadGroups();
  std::shared_ptr<GroupsCollection> groups_collection = kohot.getGroupsCollection();

  QApplication a(argc, argv);
  WindowsManager window(groups_collection);
  QObject::connect(&window, &QObject::destroyed, [&kohot]()
                   { kohot.saveGroups(); });

  ret_val = a.exec();

  return ret_val;
}
