#include "include/mainwindow.h"

#include <QApplication>

#include <QGuiApplication>
#include <QScreen>

#include "groups_manager_menu.hpp"
#include "kohot.hpp"

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

    MainWindow main_window(groups_collection);
    QObject::connect(&main_window, &QObject::destroyed,
                     [&]() { kohot.saveGroups(); });
    
    QScreen *primaryScreen = QGuiApplication::primaryScreen();

    QRect screenGeometry = primaryScreen->geometry();
    int x = (screenGeometry.width() - main_window.size().width()) / 2;
    int y = (screenGeometry.height() - main_window.size().height()) / 2;
    main_window.move(x, y);
    main_window.show();


    ret_val = a.exec();
  }

  return ret_val;
}
