#include "player_input_dialog.hpp"

#include "message_box_util.hpp"
#include "settings.hpp"

#include <QDialogButtonBox>
#include <QFormLayout>

namespace labels
{
constexpr const char* NAME = "Name:";
constexpr const char* RATE = "Rate:";
constexpr const char* ROLE = "Role:";

} // namespace labels

namespace role_options
{
constexpr const char* BALLER = "Baller";
constexpr const char* GK     = "GK";

} // namespace role_options

PlayerInputDialog::PlayerInputDialog(QWidget* parent)
    : QDialog(parent),
      m_name_line_edit(std::make_unique<QLineEdit>(this)),
      m_rate_spin_box(std::make_unique<QDoubleSpinBox>(this)),
      m_role_combo_box(std::make_unique<QComboBox>(this))
{
    static constexpr const char* WINDOW_TITLE = "Create new player";
    setWindowTitle(WINDOW_TITLE);

    m_rate_spin_box->setRange(
        Settings::getPlayerRateRange()[0],
        Settings::getPlayerRateRange()[1]);
    m_rate_spin_box->setSingleStep(1);

    m_role_combo_box->addItems({role_options::BALLER, role_options::GK});

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PlayerInputDialog::onAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PlayerInputDialog::reject);

    QFormLayout* form_layout = new QFormLayout(this);
    form_layout->addRow(labels::NAME, m_name_line_edit.get());
    form_layout->addRow(labels::RATE, m_rate_spin_box.get());
    form_layout->addRow(labels::ROLE, m_role_combo_box.get());

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
        static constexpr const char* MESSAGE = "Name cannot be empty.";
        MessageBoxUtil::show(MESSAGE, MessageBoxUtil::Type::Critical);
    }
}

bool PlayerInputDialog::validateInput() const
{
    return !m_name_line_edit->text().isEmpty();
}