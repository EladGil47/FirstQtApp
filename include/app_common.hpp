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
    const QFont HEADER_LABEL_FONT = QFont(Common::FONT_FAMILY_NAME, 22, QFont::Bold);

}

namespace Sizes
{
    const QSize WIDGET_IN_GROUP_ITEM_WIDGET = QSize(150, 35);
    const QSize WIDGET_IN_PLAYER_ITEM_WIDGET = QSize(150, 30);
}

namespace Colors{
    const QString OFFWHITE = "#FFFFBF;";

    const QString GREEN = "#4CAF50;";
    const QString HOVER_GREEN = "#45a049;";

    const QString RED = "#FF0000;";
    const QString HOVER_RED = "#FF3333;";

    const QString BLUE = "#0074CC;";
    const QString HOVER_BLUE = "#005FAA;";

    const QString TRANSPARENT = "transparent;";
}

namespace CssKeys
{
    const QString BACKGROUND_COLOR = "background-color:";
    const QString BORDER = "border:";
}

namespace Style
{
    const QString OFFWHITE_BACKGROUND = CssKeys::BACKGROUND_COLOR + Colors::OFFWHITE;

    const QString TRANSPARENT_STYLESHEET =
        CssKeys::BORDER + Colors::TRANSPARENT + CssKeys::BACKGROUND_COLOR + Colors::TRANSPARENT;

    const QString GREEN_COLOR =
        CssKeys::BORDER + Colors::GREEN + CssKeys::BACKGROUND_COLOR + Colors::GREEN;

    const QString HOVER_GREEN_COLOR =
        CssKeys::BORDER + Colors::HOVER_GREEN + CssKeys::BACKGROUND_COLOR + Colors::HOVER_GREEN;

    const QString RED_COLOR =
        CssKeys::BORDER + Colors::RED + CssKeys::BACKGROUND_COLOR + Colors::RED;

    const QString HOVER_RED_COLOR =
        CssKeys::BORDER + Colors::HOVER_RED + CssKeys::BACKGROUND_COLOR + Colors::HOVER_RED;

    const QString BLUE_COLOR =
        CssKeys::BORDER + Colors::BLUE + CssKeys::BACKGROUND_COLOR + Colors::BLUE;

    const QString HOVER_BLUE_COLOR =
        CssKeys::BORDER + Colors::HOVER_BLUE + CssKeys::BACKGROUND_COLOR + Colors::HOVER_BLUE;

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