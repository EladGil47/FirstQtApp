#ifndef FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H
#define FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

class EditableLabel : public QWidget
{
    Q_OBJECT

public:
    EditableLabel(QWidget* parent = nullptr);
    void setEditablity(bool state);
    void setFont(const QFont & font) ;
    void setAlignment(Qt::Alignment alignment) ; 
    void setText(const QString &text) ; 
    void setToolTip(const QString &text);
    void setMaxLength(uint16_t value);

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    void createLabel() ;
    void createHorLayout();
    void createEditLine() ;
    
    QLabel* m_label;
    QLineEdit* m_editLine;
    QHBoxLayout *m_layout;

    bool m_editability = true;

public slots:
    void finishEditing();

signals:
    void finishEditingSig(const QString &text);
};

#endif // FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H