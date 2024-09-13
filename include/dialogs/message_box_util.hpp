#ifndef FIRST_QT_APP_INCLUDE_MESSAGE_BOX_UTIL_HPP
#define FIRST_QT_APP_INCLUDE_MESSAGE_BOX_UTIL_HPP

#include <QMessageBox>

class MessageBoxUtil
{
public:
    enum class Type
    {
        Info,
        Warning,
        Critical,
        Question
    };
    static void show(const QString& text, Type type = Type::Info);
};

#endif // FIRST_QT_APP_INCLUDE_MESSAGE_BOX_UTIL_HPP
