#include "editable_label.h"
#include <QMouseEvent>

EditableLabel::EditableLabel(QWidget *parent) : QWidget(parent)
{
    createLabel();
    createEditLine();
    createHorLayout();
}

void EditableLabel::createHorLayout()
{
    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_editLine);
}

void EditableLabel::setText(const QString &text)
{
    m_label->setText(text);
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
    m_label = new QLabel(this);
    m_label->setToolTip("Double-click me to edit");
}

void EditableLabel::setAlignment(Qt::Alignment alignment)
{
    m_label->setAlignment(alignment);
    m_editLine->setAlignment(alignment);
}

void EditableLabel::setFont (const QFont & font)
{
    m_label->setFont(font);
    m_editLine->setFont(font);
}

void EditableLabel::createEditLine()
{
    m_editLine = new QLineEdit(this);
    const QString TRANSPARENT_LINE_EDIT_STYLESHEET =  
        "QLineEdit {"
        "    border: transparent;"
        "    background-color : transparent"
        "}"
        ;
    m_editLine->setStyleSheet(TRANSPARENT_LINE_EDIT_STYLESHEET);
    m_editLine->size() = m_label->size();
    m_editLine->setFont(m_label->font());
    m_editLine->setAlignment(m_label->alignment());
    m_editLine->setVisible(false);
    connect(m_editLine, &QLineEdit::editingFinished, this, &EditableLabel::finishEditing);
}

void EditableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (m_editability)
    {
        if (event->button() == Qt::LeftButton)
        {
            const QString ORIGINAL_TEXT = m_label->text();
            m_label->setVisible(false);
            m_editLine->setText(ORIGINAL_TEXT);
            m_editLine->setVisible(true);
            m_editLine->setFocus();
        }
    }
}

void EditableLabel::finishEditing()
{
    QString newText = m_editLine->text();
    m_label->setText(newText);
    m_label->setVisible(true);
    m_editLine->setVisible(false);
    emit finishEditingSig(newText);
}