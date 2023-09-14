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
    QLineEdit * getLineEdit() ;
    void setFont(const QFont & font) ;
    void setAlignment(Qt::Alignment alignment) ; 


    void setEditLine() ;


protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    void setLabel() ;

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
