#include "editable_label.h"
#include <QMouseEvent>

EditableLabel::EditableLabel(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    setLabel();
    layout->addWidget(m_label);

    if (m_editability)
    {
        setEditLine();
        layout->addWidget(m_editLine);
    }
}

QLabel * EditableLabel::getLabel()
{
    return m_label;
}

QLineEdit * EditableLabel::getLineEdit()
{
    return m_editLine;
}

void EditableLabel::setEditablity(bool state)
{
    m_editability = state;
}

void EditableLabel::setLabel()
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

void EditableLabel::setEditLine()
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
            m_originalText = m_label->text();
            m_label->setVisible(false);
            m_editLine->setText(m_originalText);
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