#ifndef FIRST_QT_APP_INCLUDE_APP_COMMON_H
#define FIRST_QT_APP_INCLUDE_APP_COMMON_H

#include <QDebug>
#include <QFont>
#include <QSize>
#include <QString>

#include "fonts.hpp"

enum class COLOR
{
    GREEN,
    BLUE,
    ORANGE,
    RED,
    YELLOW,
    PINK,
    PURPLE,
    GREY
};

namespace Colors
{
const QString YELLOW = "yellow;";
const QString PINK   = "pink;";
const QString PURPLE = "purpel;";
const QString GREY   = "grey;";
const QString BLACK  = "black;";

const QString OFFWHITE = "#FFFFBF;";

const QString ORANGE = "#FFA500;";

// const QString BROWN = " rgb(139, 69, 30);";
const QString BROWN = "#E3B778;";

const QString DARK_BROWN       = "#795C34;";
const QString HOVER_DARK_BROWN = "#798F67;";

const QString GREEN       = "#4CAF50;";
const QString HOVER_GREEN = "#45a049;";

const QString RED       = "#FF0000;";
const QString HOVER_RED = "#FF3333;";

const QString BLUE       = "#0074CC;";
const QString HOVER_BLUE = "#005FAA;";

const QString TRANSPARENT = "transparent;";
} // namespace Colors

namespace CssKeys
{
const QString BACKGROUND_COLOR = "background-color:";
const QString BORDER           = "border:";
} // namespace CssKeys

namespace QtObjects
{
const QString QMAIN_WINDOW = "QMainWindow";
const QString QPUSH_BUTTON = "QPushButton";
const QString QDIALOG      = "QDialog";
const QString QMESSAGEBOX  = "QMessageBox";

} // namespace QtObjects

namespace Sizes
{
const QSize WIDGET_IN_GROUP_ITEM_WIDGET  = QSize(150, 35);
const QSize WIDGET_IN_PLAYER_ITEM_WIDGET = QSize(150, 30);
} // namespace Sizes

namespace Style
{
const QString OFFWHITE_BACKGROUND = CssKeys::BACKGROUND_COLOR + Colors::OFFWHITE;

const QString TRANSPARENT_STYLESHEET =
    CssKeys::BORDER + Colors::TRANSPARENT + ";" + CssKeys::BACKGROUND_COLOR + Colors::TRANSPARENT + ";";

const QString DARK_BROWN_COLOR =
    CssKeys::BORDER + Colors::DARK_BROWN + CssKeys::BACKGROUND_COLOR + Colors::DARK_BROWN;

const QString GREEN_COLOR =
    CssKeys::BORDER + Colors::GREEN + CssKeys::BACKGROUND_COLOR + Colors::GREEN;

const QString GREEN_COLOR_BLACK_BORDER =
    CssKeys::BORDER + "1px solid " + Colors::BLACK + CssKeys::BACKGROUND_COLOR + Colors::GREEN;

const QString HOVER_DARK_BROWN_COLOR =
    CssKeys::BORDER + Colors::HOVER_DARK_BROWN + CssKeys::BACKGROUND_COLOR + Colors::HOVER_DARK_BROWN;

const QString HOVER_GREEN_COLOR =
    CssKeys::BORDER + Colors::HOVER_GREEN + CssKeys::BACKGROUND_COLOR + Colors::HOVER_GREEN;

const QString RED_COLOR =
    CssKeys::BORDER + Colors::RED + CssKeys::BACKGROUND_COLOR + Colors::RED;

const QString RED_BACKGROUND_BLACK_BORDER_WHITE_TEXT =
    CssKeys::BORDER + "1px solid " + Colors::BLACK + CssKeys::BACKGROUND_COLOR + Colors::RED + "color: white;";

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

const QString BLACK_TEXT_COLOR =
    "    color: black;"      // White text color
    "    padding: 3px 20px;" // Padding around the text
    "    font-size: 18px;"   // Font size
    "    font-weight: bold;" // Bold text
    ;

const QString DARK_BROWN_BUTTON_HOR_LAYOUT =
    QtObjects::QPUSH_BUTTON + "{" + DARK_BROWN_COLOR + WHITE_TEXT_COLOR + "}" +
    QtObjects::QPUSH_BUTTON + ":hover {" + HOVER_DARK_BROWN_COLOR + "}";

const QString GREEN_BUTTON_HOR_LAYOUT =
    QtObjects::QPUSH_BUTTON + "{" + GREEN_COLOR + WHITE_TEXT_COLOR + "}" +
    QtObjects::QPUSH_BUTTON + ":hover {" + HOVER_GREEN_COLOR + "}";

const QString RED_BUTTON_HOR_LAYOUT =
    QtObjects::QPUSH_BUTTON + " {" + RED_COLOR + WHITE_TEXT_COLOR + "}" +
    QtObjects::QPUSH_BUTTON + ":hover {" + HOVER_RED_COLOR + "}";

const QString BLUE_BUTTON_HOR_LAYOUT =
    QtObjects::QPUSH_BUTTON + " {" + BLUE_COLOR + WHITE_TEXT_COLOR + "}" +
    QtObjects::QPUSH_BUTTON + ":hover {" + HOVER_BLUE_COLOR + "}";

const QString LIST = "QListWidget {" + CssKeys::BORDER + "1px solid " + Colors::BLACK + ";" + CssKeys::BACKGROUND_COLOR + Colors::BROWN + "}"
                                                                                                                                          "QListWidget::item {" +
                     CssKeys::BORDER + "1px solid " + Colors::BLACK + ";" + "}"
                                                                            "QListWidget::item:selected {" +
                     CssKeys::BACKGROUND_COLOR + "rgba(0, 0, 255, 10%) " + ";" + " } ";

const QString ORANGE_LIST = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::ORANGE + "}";
const QString GREEN_LIST  = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::GREEN + "}";
const QString BLUE_LIST   = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::BLUE + "}";
const QString RED_LIST    = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::RED + "}";
const QString YELLOW_LIST = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::YELLOW + "}";

} // namespace Style

namespace ui_settings
{
const QString WINDOWS_COLOR             = QtObjects::QMAIN_WINDOW + "{" + Style::OFFWHITE_BACKGROUND + "}";
const QString DIALOGS_COLOR             = QtObjects::QDIALOG + "{" + Style::OFFWHITE_BACKGROUND + "}";
const QString MESSAGES_BOX_COLOR        = QtObjects::QMESSAGEBOX + "{" + Style::OFFWHITE_BACKGROUND + "}";
const QString BOTTOM_BUTTONS_LINE_COLOR = Style::DARK_BROWN_BUTTON_HOR_LAYOUT;
} // namespace ui_settings

namespace MaxValues
{
const uint16_t ITEM_WIDGET_LABEL_NAME = 15;
const uint16_t MAX_GROUP_SIZE         = 999;
} // namespace MaxValues

namespace Functions
{
// Create a reusable function to check and log errors
template <typename T>
void checkNotNull(T* object, const QString& object_name)
{
    if (object == nullptr)
    {
        qCritical() << "Error:" << object_name << "is nullptr";
    }
}
template <typename T>
void checkNotNull(std::shared_ptr<T> object, const QString& object_name)
{
    if (object == nullptr)
    {
        qCritical() << "Error:" << object_name << "is nullptr";
    }
}
} // namespace Functions

#endif // FIRST_QT_APP_INCLUDE_APP_COMMON_H