#include <QApplication>

#include "kohot.hpp"
#include "resource_paths.hpp"
#include "windows_manager.hpp"

#include <QMediaPlayer>
#include <QTimer>
#include <QUrl>

int main(int argc, char* argv[])
{
    int   ret_val = EXIT_SUCCESS;
    Kohot kohot;
    kohot.loadGroups();
    std::shared_ptr<GroupsCollection> groups_collection = kohot.getGroupsCollection();

    QApplication a(argc, argv);

    QMediaPlayer player;

    // Set the media source to the music file
    player.setMedia(QUrl(resources_path::SONG));

    // Start playback
    player.play();

    // To keep the application running while the music plays
    QTimer::singleShot(0, [&player]() {
        player.play(); // Start playback again if stopped
    });

    a.setWindowIcon(QIcon(resources_path::SOCCER_BALL));
    WindowsManager window(groups_collection);
    QObject::connect(&window, &QObject::destroyed, [&kohot]() { kohot.saveGroups(); });

    ret_val = a.exec();

    return ret_val;
}
