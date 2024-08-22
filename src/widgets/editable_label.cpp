#include "editable_label.hpp"
#include "app_common.hpp"

#include <QMouseEvent>

EditableLabel::EditableLabel(bool is_numeric)
    : m_is_numeric(is_numeric)
{
    createLabel();
    if (m_is_numeric)
    {
        createSpinBox();
    }
    else
    {
        createEditLine();
    }
    createHorLayout();
}

void EditableLabel::createEditLine()
{
    m_edit_line = new QLineEdit;
    m_edit_line->setStyleSheet(Style::TRANSPARENT_STYLESHEET);
    m_edit_line->size() = m_label->size();
    m_edit_line->setFont(m_label->font());
    m_edit_line->setAlignment(m_label->alignment());
    m_edit_line->setVisible(false);
    connect(m_edit_line, &QLineEdit::editingFinished, this, &EditableLabel::finishEditing);
}

void EditableLabel::createSpinBox()
{
    m_spin_box         = new QDoubleSpinBox;
    m_spin_box->size() = m_label->size();
    m_spin_box->setFont(m_label->font());
    m_spin_box->setAlignment(m_label->alignment());
    m_spin_box->setRange(0, 7); //TODO:: read it from some settings
    m_spin_box->setSingleStep(1);
    m_spin_box->setVisible(false);
    connect(m_spin_box, &QDoubleSpinBox::editingFinished, this, &EditableLabel::finishEditing);
}

void EditableLabel::createHorLayout()
{
    m_layout = new QHBoxLayout(this);
    if (m_label != nullptr)
        m_layout->addWidget(m_label);
    if (m_edit_line != nullptr)
        m_layout->addWidget(m_edit_line);
    if (m_spin_box != nullptr)
        m_layout->addWidget(m_spin_box);
}

void EditableLabel::setText(const QString& text)
{
    m_label->setText(text);
}

void EditableLabel::setPixmap(const QPixmap& pixmap)
{
    if (pixmap.isNull())
    {
        qWarning("Failed to load image");
    }
    else
    {
        m_label->setPixmap(pixmap);
    }
}

void EditableLabel::setEditablity(bool state)
{
    m_editability = state;
    if (!m_editability)
    {
        m_label->setToolTip(nullptr);
    }
}

void EditableLabel::createLabel()
{
    m_label = new QLabel;
    m_label->setToolTip("Double-click me to edit");
}

void EditableLabel::setToolTip(const QString& text)
{
    m_label->setToolTip(text);
}

void EditableLabel::setAlignment(Qt::Alignment alignment)
{
    m_label->setAlignment(alignment);
    if (m_edit_line != nullptr)
        m_edit_line->setAlignment(alignment);
}

void EditableLabel::setFont(const QFont& font)
{
    m_label->setFont(font);
    if (m_edit_line != nullptr)
        m_edit_line->setFont(font);
}

void EditableLabel::setMaxLength(uint16_t value)
{
    if (m_edit_line != nullptr)
        m_edit_line->setMaxLength(value);
}

void EditableLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (m_editability)
    {
        if (event->button() == Qt::LeftButton)
        {
            QString original_text = m_label->text();
            m_label->setVisible(false);
            if (m_is_numeric)
            {
                m_spin_box->setFocus();
                bool ok;
                m_spin_box->setValue(original_text.toDouble(&ok));
                m_spin_box->setVisible(true);
            }
            else
            {
                m_edit_line->setText(original_text);
                m_edit_line->setVisible(true);
                m_edit_line->setFocus();
            }
        }
    }
}

void EditableLabel::finishEditing()
{
    QString newText;
    if (m_is_numeric)
    {
        m_spin_box->setVisible(false);
        auto value = m_spin_box->value();
        newText    = QString::number(value, 'f', 2);
    }

    else
    {
        m_edit_line->setVisible(false);
        newText = m_edit_line->text();
    }

    m_label->setText(newText);
    m_label->setVisible(true);
    emit finishEditingSig(newText);
}