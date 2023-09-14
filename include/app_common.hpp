#ifndef FIRST_QT_APP_INCLUDE_APP_COMMON_H
#define FIRST_QT_APP_INCLUDE_APP_COMMON_H

#include <QString>

namespace Common
{
    const QString FONT_FAMILY_NAME = "Segoe UI";
}

namespace Style
{
    const QString TRANSPARENT_STYLESHEET =  
        "    border: transparent;"
        "    background-color : transparent"
        ;
}


namespace MaxValues
{
    const uint16_t ITEM_WIDGET_LABEL_NAME = 15 ;
    const uint16_t MAX_GROUP_SIZE = 999 ;

      
}

#endif //FIRST_QT_APP_INCLUDE_APP_COMMON_H