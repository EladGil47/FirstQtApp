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

QLabel * EditableLabel::getLabel()
{
    return m_label;
}

void EditableLabel::setEditablity(bool state)
{
    m_editability = state;
}

void EditableLabel::setLabel()
{
    m_label = new QLabel(this);
    QString header_label_stylesheet =
        "QLabel {"
        "    color: black;"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "}";
    m_label->setStyleSheet(header_label_stylesheet);
    m_label->setAlignment(Qt::AlignHCenter);
    m_label->setToolTip("Double-click me to edit");
}

void EditableLabel::setEditLine()
{
    m_editLine = new QLineEdit(this);

    QString edit_line_stylesheet =
        "QLineEdit {"
        "    color: black;"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "    border: transparent;"
        "    background-color : #FFFFBF"
        "}";
    m_editLine->setStyleSheet(edit_line_stylesheet);
    m_editLine->setAlignment(Qt::AlignHCenter);
    m_editLine->setVisible(false);
    connect(m_editLine, &QLineEdit::editingFinished, this, &EditableLabel::finishEditing);
}