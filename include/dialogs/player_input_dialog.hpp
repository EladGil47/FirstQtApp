#ifndef FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP
#define FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>

class PlayerInputDialog : public QDialog
{
    Q_OBJECT
public:
    PlayerInputDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        setWindowTitle("Create new player");

        m_name_line_edit = new QLineEdit(this);

        m_rate_spin_box = new QDoubleSpinBox(this);
        m_rate_spin_box->setRange(0, 7);
        m_rate_spin_box->setSingleStep(1);

        m_role_combo_box = new QComboBox(this);
        m_role_combo_box->addItem("Baller");
        m_role_combo_box->addItem("GK");

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &PlayerInputDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &PlayerInputDialog::reject);

        QFormLayout *form_layout = new QFormLayout(this);
        form_layout->addRow("Name:", m_name_line_edit);
        form_layout->addRow("Rate:", m_rate_spin_box);
        form_layout->addRow("Role:", m_role_combo_box);

        form_layout->addWidget(buttonBox);
    }

    QString getPlayerName() const
    {
        return m_name_line_edit->text();
    }

    QString getPlayerRole() const
    {
        return m_role_combo_box->currentText();
    }

    double getPlayerRate() const
    {
        return m_rate_spin_box->value();
    }

private:
    QLineEdit *m_name_line_edit;
    QDoubleSpinBox *m_rate_spin_box;
    QComboBox *m_role_combo_box;
};

#endif // FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP