#ifndef FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H
#define FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QWidget>
#include <memory>

class EditableLabel : public QWidget
{
    Q_OBJECT

public:
    EditableLabel(bool is_numeric = false);

    void setEditability(bool state);
    void setFont(const QFont& font);
    void setAlignment(Qt::Alignment alignment);
    void setText(const QString& text);
    void setToolTip(const QString& text);
    void setMaxLength(uint16_t value);
    void setPixmap(const QPixmap& pixmap);

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    void createLabel();
    void createHorLayout();
    void createEditLine();
    void createSpinBox();

    std::shared_ptr<QLabel>         m_label;
    std::shared_ptr<QLineEdit>      m_edit_line;
    std::shared_ptr<QDoubleSpinBox> m_spin_box;
    std::shared_ptr<QHBoxLayout>    m_layout;

    bool m_editability{true};
    bool m_is_numeric{false};

public slots:
    void finishEditing();

signals:
    void finishEditingSig(const QString& text);
};

#endif // FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H
