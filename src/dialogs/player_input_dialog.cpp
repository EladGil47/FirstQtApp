#include "player_input_dialog.hpp"
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QMessageBox>

#include "settings.hpp"

constexpr const char* WINDOW_TITLE = "Create new player";
constexpr const char* NAME_LABEL   = "Name:";
constexpr const char* RATE_LABEL   = "Rate:";
constexpr const char* ROLE_LABEL   = "Role:";
constexpr const char* BALLER_LABEL = "Baller";
constexpr const char* GK_LABEL     = "GK";

PlayerInputDialog::PlayerInputDialog(QWidget* parent)
    : QDialog(parent),
      m_name_line_edit(std::make_unique<QLineEdit>(this)),
      m_rate_spin_box(std::make_unique<QDoubleSpinBox>(this)),
      m_role_combo_box(std::make_unique<QComboBox>(this))
{
    setWindowTitle(WINDOW_TITLE);

    m_rate_spin_box->setRange(
        Settings::getPlayerRateRange()[0],
        Settings::getPlayerRateRange()[1]);
    m_rate_spin_box->setSingleStep(1);

    m_role_combo_box->addItems({BALLER_LABEL, GK_LABEL});

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PlayerInputDialog::onAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PlayerInputDialog::reject);

    QFormLayout* form_layout = new QFormLayout(this);
    form_layout->addRow(NAME_LABEL, m_name_line_edit.get());
    form_layout->addRow(RATE_LABEL, m_rate_spin_box.get());
    form_layout->addRow(ROLE_LABEL, m_role_combo_box.get());

    form_layout->addWidget(buttonBox);
}

QString PlayerInputDialog::getPlayerName() const
{
    return m_name_line_edit->text();
}

QString PlayerInputDialog::getPlayerRole() const
{
    return m_role_combo_box->currentText();
}

double PlayerInputDialog::getPlayerRate() const
{
    return m_rate_spin_box->value();
}

void PlayerInputDialog::onAccepted()
{
    if (validateInput())
    {
        accept();
    }
    else
    {
        static constexpr const char* ERROR_MESSAGE = "Name cannot be empty.";
        QMessageBox::warning(this, WINDOW_TITLE, ERROR_MESSAGE);
    }
}

bool PlayerInputDialog::validateInput() const
{
    return !m_name_line_edit->text().isEmpty();
}