#ifndef FIRST_QT_APP_INCLUDE_APP_COMMON_H
#define FIRST_QT_APP_INCLUDE_APP_COMMON_H

#include <QString>
#include <QSize>
#include <QDebug>

#include <memory>

namespace Settings
{
    const QString WINDOW_TITLE_TEXT = "Kohot";
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const QString BACKGROUND_COLOR = "QMainWindow{background-color : #FFFFBF}";
}

namespace Common
{
    const QString FONT_FAMILY_NAME = "Segoe UI";
}

namespace Fonts
{
    const QFont PLAYER_ITEM_WIDGET_FONT = QFont(Common::FONT_FAMILY_NAME, 12, QFont::Bold);
    const QFont GROUP_ITEM_WIDGET_FONT = QFont(Common::FONT_FAMILY_NAME, 14, QFont::Bold);
    const QFont LIST_LABEL_FONT = QFont(Common::FONT_FAMILY_NAME, 18, QFont::Bold);
    const QFont HEADER_LABEL_FONT = QFont(Common::FONT_FAMILY_NAME, 26, QFont::Bold);

}

namespace Sizes
{
    const QSize WIDGET_IN_GROUP_ITEM_WIDGET = QSize(150, 40);

}

namespace Style
{
    const QString TRANSPARENT_STYLESHEET =
        "border: transparent;"
        "background-color: transparent;";

    const QString GREEN_COLOR =
        "    background-color: #4CAF50;"
        "    border: 2px solid #4CAF50;";

    const QString HOVER_GREEN_COLOR =
        "    background-color: #45a049;"
        "    border: 2px solid #45a049;";

    const QString RED_COLOR =
        "    background-color: #FF0000;"
        "    border: 2px solid #FF0000;";

    const QString HOVER_RED_COLOR =
        "    background-color: #FF3333;"
        "    border: 2px solid #FF3333;";

    const QString BLUE_COLOR =
        "    background-color: #0074CC;"
        "    border: 2px solid #0074CC;";

    const QString HOVER_BLUE_COLOR =
        "    background-color: #005FAA;"
        "    border: 2px solid #005FAA;";

    const QString WHITE_TEXT_COLOR =
        "    color: white;"      // White text color
        "    padding: 3px 20px;" // Padding around the text
        "    font-size: 18px;"   // Font size
        "    font-weight: bold;" // Bold text
        ;

    const QString GREEN_BUTTON_HOR_LAYOUT =
        "QPushButton {" + GREEN_COLOR + WHITE_TEXT_COLOR + "}"
        "QPushButton:hover {" + HOVER_GREEN_COLOR + "}";

    const QString RED_BUTTON_HOR_LAYOUT =
        "QPushButton {" + RED_COLOR + WHITE_TEXT_COLOR +"}"
        "QPushButton:hover {" + HOVER_RED_COLOR + "}";

    const QString BLUE_BUTTON_HOR_LAYOUT =
        "QPushButton {" + BLUE_COLOR + WHITE_TEXT_COLOR +"}"
        "QPushButton:hover {" + HOVER_BLUE_COLOR + "}";
}

namespace MaxValues
{
    const uint16_t ITEM_WIDGET_LABEL_NAME = 15;
    const uint16_t MAX_GROUP_SIZE = 999;
}

namespace Functions
{
    // Create a reusable function to check and log errors
    template <typename T>
    void checkNotNull(T *object, const QString &object_name)
    {
        if (object == nullptr)
        {
            qCritical() << "Error:" << object_name << "is nullptr";
        }
    }
    template <typename T>
    void checkNotNull(std::shared_ptr<T> object, const QString &object_name)
    {
        if (object == nullptr)
        {
            qCritical() << "Error:" << object_name << "is nullptr";
        }
    }
}

#endif // FIRST_QT_APP_INCLUDE_APP_COMMON_H