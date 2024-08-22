#include "editable_label.hpp"
#include "app_common.hpp"

#include <QMouseEvent>

EditableLabel::EditableLabel(bool is_numeric)
    : m_is_numeric(is_numeric)
{
    createLabel();
    m_is_numeric ? createSpinBox() : createEditLine();
    createHorLayout();
}

template <typename T>
void EditableLabel::initializeWidget(std::shared_ptr<T>& widget)
{
    widget = std::make_shared<T>();
    widget->setSizePolicy(m_label->sizePolicy());
    widget->setFont(m_label->font());
    widget->setAlignment(m_label->alignment());
    widget->setVisible(false);
    connect(widget.get(), &T::editingFinished, this, &EditableLabel::finishEditing);
}

void EditableLabel::createEditLine()
{
    initializeWidget(m_edit_line);
    m_edit_line->setStyleSheet(Style::TRANSPARENT_STYLESHEET);
}

void EditableLabel::createSpinBox()
{
    initializeWidget(m_spin_box);
    m_spin_box->setRange(0, 7); // TODO: read it from some settings
    m_spin_box->setSingleStep(1);
}

void EditableLabel::createHorLayout()
{
    m_layout = std::make_shared<QHBoxLayout>(this);
    if (m_label)
        m_layout->addWidget(m_label.get());
    if (m_edit_line)
        m_layout->addWidget(m_edit_line.get());
    if (m_spin_box)
        m_layout->addWidget(m_spin_box.get());
}

void EditableLabel::setText(const QString& text)
{
    m_label->setText(text);
}

void EditableLabel::setEditability(bool state)
{
    m_editability = state;
    if (!m_editability)
    {
        m_label->setToolTip(nullptr);
    }
}

void EditableLabel::createLabel()
{
    static constexpr const char* TOOL_TIP_MSG = "Double-click me to edit";

    m_label = std::make_shared<QLabel>();
    m_label->setToolTip(TOOL_TIP_MSG);
}

void EditableLabel::setAlignment(Qt::Alignment alignment)
{
    m_label->setAlignment(alignment);
    if (m_edit_line)
        m_edit_line->setAlignment(alignment);
}

void EditableLabel::setFont(const QFont& font)
{
    m_label->setFont(font);
    if (m_edit_line)
        m_edit_line->setFont(font);
}

void EditableLabel::setMaxLength(uint16_t value)
{
    if (m_edit_line)
        m_edit_line->setMaxLength(value);
}

void EditableLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (m_editability && event->button() == Qt::LeftButton)
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

void EditableLabel::finishEditing()
{
    QString newText;
    if (m_is_numeric)
    {
        m_spin_box->setVisible(false);
        newText = QString::number(m_spin_box->value(), 'f', 2);
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
