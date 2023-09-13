#include "include/mainwindow.h"
#include "include/group_menu_window.h"


#include <QApplication>

#include <QGuiApplication>
#include <QScreen>

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

    // MainWindow * main_window = new MainWindow(groups_collection,&window);
    // window.setCentralWidget(main_window);
    // window.show();

    // window.setMainWindowAsCentralWidget();

    // QObject::connect(main_window, MainWindow::switchToGroupMenuWidget,
    //                  [&window, &groups_collection](size_t id)
    //                  {
    //                    qDebug() << " Hello from Main";
    //                    std::shared_ptr<Group> group = groups_collection->getItem(id);
    //                    GroupMenuWindow *group_menu_window = new GroupMenuWindow(group, &window);
    //                    group_menu_window->init();
    //                    window.setCentralWidget(group_menu_window);
    //                  });


                

    // This is How to switch QWidget on window
    // QWidget * ss = new QWidget(&window);
    // window.setCentralWidget(ss);


    ret_val = a.exec();
  }

  return ret_val;
}
