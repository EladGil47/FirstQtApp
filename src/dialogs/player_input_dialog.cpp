#include "player_input_dialog.hpp"

#include "app_common.hpp"
#include "message_box_util.hpp"
#include "settings.hpp"

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
    setWindowTitle(WINDOW_TITLE);
    setStyleSheet(ui_settings::DIALOGS_COLOR);

    m_rate_spin_box->setRange(
        Settings::getPlayerRateRange()[0],
        Settings::getPlayerRateRange()[1]);
    m_rate_spin_box->setSingleStep(1);

    m_role_combo_box->addItems({role_options::BALLER, role_options::GK});

    m_button_box = std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(m_button_box.get(), &QDialogButtonBox::accepted, this, &PlayerInputDialog::onAccepted);
    connect(m_button_box.get(), &QDialogButtonBox::rejected, this, &PlayerInputDialog::reject);

    m_form_layout = std::make_unique<QFormLayout>(this);
    m_form_layout->addRow(labels::NAME, m_name_line_edit.get());
    m_form_layout->addRow(labels::RATE, m_rate_spin_box.get());
    m_form_layout->addRow(labels::ROLE, m_role_combo_box.get());

    m_form_layout->addWidget(m_button_box.get());
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
    bool is_valid = validateInput();
    if (is_valid)
    {
        accept();
    }
}

bool PlayerInputDialog::validateInput() const
{
    bool is_valid = !m_name_line_edit->text().isEmpty();
    if (!is_valid)
    {
        static constexpr const char* MESSAGE = "Name cannot be empty.";
        MessageBoxUtil::show(MESSAGE, MessageBoxUtil::Type::Critical);
    }

    return is_valid;
}