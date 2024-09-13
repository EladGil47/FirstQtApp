#include "group_input_dialog.hpp"

#include "message_box_util.hpp"
#include "settings.hpp"

namespace labels
{
constexpr const char* NAME            = "Name:";
constexpr const char* TEAMS           = "Teams:";
constexpr const char* PLAYERS_IN_TEAM = "Players in team:";

} // namespace labels

GroupInputDialog::GroupInputDialog(QWidget* parent)
    : QDialog(parent)
{
    static constexpr const char* WINDOW_TITLE = "Create new group";
    setWindowTitle(WINDOW_TITLE);

    m_name_line_edit = std::make_unique<QLineEdit>(this);

    m_teams_spin_box = std::make_unique<QSpinBox>(this);
    m_teams_spin_box->setRange(
        Settings::getTeamsRange()[0],
        Settings::getTeamsRange()[1]);

    m_players_in_team_spin_box = std::make_unique<QSpinBox>(this);
    m_players_in_team_spin_box->setRange(
        Settings::getPlayersInTeamRange()[0],
        Settings::getPlayersInTeamRange()[1]);

    m_button_box = std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    m_layout = std::make_unique<QFormLayout>(this);
    m_layout->addRow(labels::NAME, m_name_line_edit.get());
    m_layout->addRow(labels::TEAMS, m_teams_spin_box.get());
    m_layout->addRow(labels::PLAYERS_IN_TEAM, m_players_in_team_spin_box.get());
    m_layout->addWidget(m_button_box.get());

    connect(m_button_box.get(), &QDialogButtonBox::accepted, this, &GroupInputDialog::onAccepted);
    connect(m_button_box.get(), &QDialogButtonBox::rejected, this, &GroupInputDialog::reject);
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
    else
    {
        static constexpr const char* ERROR_MESSAGE = "Name cannot be empty.";
        MessageBoxUtil::show(ERROR_MESSAGE, MessageBoxUtil::Type::Critical);
    }
}

bool GroupInputDialog::validateInput() const
{
    return !m_name_line_edit->text().isEmpty();
}
