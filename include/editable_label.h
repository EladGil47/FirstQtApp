#ifndef EDITABLELABEL_HPP
#define EDITABLELABEL_HPP

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
    QLabel * getLabel() ;

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    void setLabel() ;
    void setEditLine() ;

    QLabel* m_label;
    QLineEdit* m_editLine;
    QString m_originalText;
    
    bool m_editability = true;

public slots:
    void finishEditing();

signals:
    void finishEditingSig(const QString &text);
};

#endif // EDITABLELABEL_HPP
