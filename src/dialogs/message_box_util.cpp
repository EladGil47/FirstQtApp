
#include "message_box_util.hpp"
#include "app_common.hpp"
#include "fonts.hpp"

void MessageBoxUtil::show(const QString& text, Type type)
{
    QMessageBox message_box;

    switch (type)
    {
        case Type::Info:
            message_box.setIcon(QMessageBox::Information);
            break;
        case Type::Warning:
            message_box.setIcon(QMessageBox::Warning);
            break;
        case Type::Critical:
            message_box.setIcon(QMessageBox::Critical);
            break;
        case Type::Question:
            message_box.setIcon(QMessageBox::Question);
            break;
    }

    message_box.setWindowTitle("Message");
    message_box.setStyleSheet(ui_settings::MESSAGES_BOX_COLOR);
    message_box.setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);

    message_box.setText(text);

    message_box.setStandardButtons(QMessageBox::Ok);
    message_box.exec();
}
