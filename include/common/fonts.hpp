#ifndef FONTS_HPP
#define FONTS_HPP

#include <QFont>
#include <QString>

namespace Fonts
{
const QString       FONT_FAMILY_NAME = "Segoe UI";
const QFont::Weight FONT_WEIGHT      = QFont::Bold;

const QFont PLAYER_ITEM_WIDGET_FONT(FONT_FAMILY_NAME, 12, FONT_WEIGHT);
const QFont GROUP_ITEM_WIDGET_FONT(FONT_FAMILY_NAME, 14, FONT_WEIGHT);
const QFont LIST_LABEL_FONT(FONT_FAMILY_NAME, 18, FONT_WEIGHT);
const QFont HEADER_LABEL_FONT(FONT_FAMILY_NAME, 22, FONT_WEIGHT);
const QFont LARGE_FONT(FONT_FAMILY_NAME, 30, FONT_WEIGHT);
} // namespace Fonts

#endif // FONTS_HPP
