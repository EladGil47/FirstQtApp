#include "group_input_dialog.hpp"

#include "app_common.hpp"
#include "message_box_util.hpp"
#include "settings.hpp"

namespace labels
{
constexpr const char* NAME            = "Name:";
constexpr const char* TEAMS           = "Teams:";
constexpr const char* PLAYERS_IN_TEAM = "Players in team:";

} // namespace labels

GroupInputDialog::GroupInputDialog(QWidget* parent)
    : QDialog(parent),
      m_name_line_edit(std::make_unique<QLineEdit>(this)),
      m_teams_spin_box(std::make_unique<QSpinBox>(this)),
      m_players_in_team_spin_box(std::make_unique<QSpinBox>(this)),
      m_button_box(std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)),
      m_form_layout(std::make_unique<QFormLayout>(this))
{
    setWindowTitle(WINDOW_TITLE);
    setStyleSheet(ui_settings::DIALOGS_COLOR);

    m_teams_spin_box->setRange(
        Settings::getTeamsRange()[0],
        Settings::getTeamsRange()[1]);

    m_players_in_team_spin_box->setRange(
        Settings::getPlayersInTeamRange()[0],
        Settings::getPlayersInTeamRange()[1]);

    connect(m_button_box.get(), &QDialogButtonBox::accepted, this, &GroupInputDialog::onAccepted);
    connect(m_button_box.get(), &QDialogButtonBox::rejected, this, &GroupInputDialog::reject);

    m_form_layout->addRow(labels::NAME, m_name_line_edit.get());
    m_form_layout->addRow(labels::TEAMS, m_teams_spin_box.get());
    m_form_layout->addRow(labels::PLAYERS_IN_TEAM, m_players_in_team_spin_box.get());
    m_form_layout->addWidget(m_button_box.get());
}

QString GroupInputDialog::getGroupName() const
{
    return m_name_line_edit->text();
}

int32_t GroupInputDialog::getTeamsAmount() const
{
    return m_teams_spin_box->value();
}

int32_t GroupInputDialog::getPlayersInTeamAmount() const
{
    return m_players_in_team_spin_box->value();
}

void GroupInputDialog::onAccepted()
{
    if (validateInput())
    {
        accept();
    }
}

bool GroupInputDialog::validateInput() const
{
    bool is_valid = !m_name_line_edit->text().isEmpty();
    if (!is_valid)
    {
        static constexpr const char* MESSAGE = "Name cannot be empty.";
        MessageBoxUtil::show(MESSAGE, MessageBoxUtil::Type::Critical);
    }

    return is_valid;
}
