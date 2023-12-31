#ifndef FIRST_QT_APP_INCLUDE_APP_COMMON_H
#define FIRST_QT_APP_INCLUDE_APP_COMMON_H

#include <QString>
#include <QFont>
#include <QSize>
#include <QDebug>

#include <memory>

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
    const QString PINK = "pink;";
    const QString PURPLE = "purpel;";
    const QString GREY = "grey;";
    const QString BLACK = "black;";

    const QString OFFWHITE = "#FFFFBF;";

    const QString ORANGE = "#FFA500;";

    const QString BROWN = " rgb(139, 69, 30);";

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

namespace QtObjects
{
    const QString QMAIN_WINDOW = "QMainWindow";
    const QString QPUSH_BUTTON = "QPushButton";
    const QString QDIALOG = "QDialog";
    const QString QMESSAGEBOX = "QMessageBox";

}

namespace Common
{
    const QString FONT_FAMILY_NAME = "Segoe UI";
}



namespace Sizes
{
    const QSize WIDGET_IN_GROUP_ITEM_WIDGET = QSize(150, 35);
    const QSize WIDGET_IN_PLAYER_ITEM_WIDGET = QSize(150, 30);
}

namespace Style
{
    const QString OFFWHITE_BACKGROUND = CssKeys::BACKGROUND_COLOR + Colors::OFFWHITE;

    const QString TRANSPARENT_STYLESHEET =
        CssKeys::BORDER + Colors::TRANSPARENT + ";" + CssKeys::BACKGROUND_COLOR + Colors::TRANSPARENT + ";";

    const QString GREEN_COLOR =
        CssKeys::BORDER + Colors::GREEN + CssKeys::BACKGROUND_COLOR + Colors::GREEN;

    const QString GREEN_COLOR_BLACK_BORDER =
        CssKeys::BORDER + "1px solid " + Colors::BLACK + CssKeys::BACKGROUND_COLOR + Colors::GREEN;

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
    const QString GREEN_LIST = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::GREEN + "}";
    const QString BLUE_LIST = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::BLUE + "}";
    const QString RED_LIST = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::RED + "}";
    const QString YELLOW_LIST = "QListWidget {" + CssKeys::BACKGROUND_COLOR + Colors::YELLOW + "}";

}

class ListStyles
{
private:
    std::vector<QString> m_team_colors = {
        Style::GREEN_LIST,
        Style::BLUE_LIST,
        Style::ORANGE_LIST,
        Style::RED_LIST};

public:
    QString getColoredListStyle(std::uint16_t index)
    {
        QString ret_val;
        if (index < m_team_colors.size())
        {
            ret_val = m_team_colors[index];
        }
        else
        {
            throw std::out_of_range("Index out of range");
        }
        return ret_val;
    }
};

namespace Settings
{
    const QString WINDOW_TITLE_TEXT = "Kohot";

    const QString FONT_FAMILY_NAME = "Segoe UI";

    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 640;

    const int POP_UP_WINDOW_WIDTH = 400;
    const int POP_UP_WINDOW_HEIGHT = 200;

    const QString WINDOWS_COLOR = QtObjects::QMAIN_WINDOW + "{" + Style::OFFWHITE_BACKGROUND + "}";
    const QString DIALOGS_COLOR = QtObjects::QDIALOG + "{" + Style::OFFWHITE_BACKGROUND + "}";
    const QString MESSAGES_BOX_COLOR = QtObjects::QMESSAGEBOX + "{" + Style::OFFWHITE_BACKGROUND + "}";
}

namespace Fonts
{
    const QFont SMALL_FONT = QFont(Common::FONT_FAMILY_NAME, 8, QFont::Bold);
    const QFont PLAYER_ITEM_WIDGET_FONT = QFont(Common::FONT_FAMILY_NAME, 12, QFont::Bold);
    const QFont GROUP_ITEM_WIDGET_FONT = QFont(Common::FONT_FAMILY_NAME, 14, QFont::Bold);
    const QFont LIST_LABEL_FONT = QFont(Common::FONT_FAMILY_NAME, 18, QFont::Bold);
    const QFont HEADER_LABEL_FONT = QFont(Common::FONT_FAMILY_NAME, 22, QFont::Bold);
    const QFont LARGE_FONT = QFont(Common::FONT_FAMILY_NAME, 30, QFont::Bold);
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

#include <QMessageBox>

class MessageBoxHandler
{
public:
    static void showMessageBox(QString message_text)
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Warning");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setStyleSheet(Settings::MESSAGES_BOX_COLOR);
        messageBox.setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);

        messageBox.setText(message_text);

        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.exec();
    }
};

#endif // FIRST_QT_APP_INCLUDE_APP_COMMON_H