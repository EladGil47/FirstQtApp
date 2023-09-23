#ifndef FIRST_QT_APP_INCLUDE_APP_COMMON_H
#define FIRST_QT_APP_INCLUDE_APP_COMMON_H

#include <QString>
#include <QSize>
#include <QDebug>


namespace Settings
{
    const QString WINDOW_TITLE_TEXT = "Kohot";
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 400;
    const QString BACKGROUND_COLOR = "QMainWindow{background-color : #FFFFBF}";
}

namespace Common
{
    const QString FONT_FAMILY_NAME = "Segoe UI";
}

namespace Style
{
    const QString TRANSPARENT_STYLESHEET =  
        "border: transparent;"
        "background-color: transparent;"
        ;

}


namespace MaxValues
{
    const uint16_t ITEM_WIDGET_LABEL_NAME = 15 ;
    const uint16_t MAX_GROUP_SIZE = 999 ;
}


namespace Functions
{
// Create a reusable function to check and log errors
template <typename T>
void checkNotNull(T* object, const QString& object_name) {
    if (object == nullptr)
    {
        qCritical() << "Error:" << object_name << "is nullptr";
    }
}
}

#endif //FIRST_QT_APP_INCLUDE_APP_COMMON_H