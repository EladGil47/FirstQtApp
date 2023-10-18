#ifndef FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP
#define FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>

class PlayerInputDialog : public QDialog
{
    Q_OBJECT
public:
    PlayerInputDialog(QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Create new player");

        nameLineEdit = new QLineEdit(this);
        rateSpinBox = new QDoubleSpinBox(this);
        rateSpinBox->setRange(0, 7);
        rateSpinBox->setSingleStep(1);

        QFormLayout* layout = new QFormLayout(this);
        layout->addRow("Name:", nameLineEdit);
        layout->addRow("Rate:", rateSpinBox);

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &PlayerInputDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &PlayerInputDialog::reject);
    }

    QString getPlayerName() const
    {
        return nameLineEdit->text();
    }

    double getPlayerRate() const
    {
        return rateSpinBox->value();
    }

private:
    QLineEdit* nameLineEdit;
    QDoubleSpinBox* rateSpinBox;
};

#endif // FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP