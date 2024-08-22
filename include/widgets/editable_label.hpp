#ifndef FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H
#define FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <memory>

class EditableLabel : public QWidget
{
    Q_OBJECT

public:
    EditableLabel(std::shared_ptr<QLabel> m_label, bool is_numeric = false);
    void setEditability(bool state);

private:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void createHorLayout();
    void createEditLine();
    void createSpinBox();

    std::shared_ptr<QLabel>         m_label;
    std::shared_ptr<QLineEdit>      m_edit_line;
    std::shared_ptr<QDoubleSpinBox> m_spin_box;
    std::shared_ptr<QHBoxLayout>    m_layout;

    bool m_editability{true};
    bool m_is_numeric{false};

    template <typename T>
    void initializeWidget(std::shared_ptr<T>& widget);

public slots:
    void finishEditing();

signals:
    void finishEditingSig(const QString& text);
};

#endif // FIRST_QT_APP_INCLUDE_EDITABLE_LABEL_H
