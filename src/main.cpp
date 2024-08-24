#include <QApplication>

#include "kohot.hpp"
#include "resource_paths.hpp"

#include "settings.hpp"
#include "windows_manager.hpp"

int32_t main(int32_t argc, char* argv[])
{
    int32_t ret_val = EXIT_SUCCESS;

    Kohot kohot;
    auto  groups_collection = kohot.getGroupsCollection();

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(resources_path::SOCCER_BALL));
    WindowsManager window(groups_collection);
    QObject::connect(&window, &QObject::destroyed, [&kohot]() { kohot.saveGroups(); });

    ret_val = a.exec();

    return ret_val;
}
