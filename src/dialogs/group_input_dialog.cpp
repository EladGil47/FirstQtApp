#include "group_input_dialog.hpp"

#include "resource_paths.hpp"
#include "settings.hpp"

#include <QMessageBox>

static constexpr const char* WINDOW_TITLE          = "Create new group";
static constexpr const char* LABEL_NAME            = "Name:";
static constexpr const char* LABEL_TEAMS           = "Teams:";
static constexpr const char* LABEL_PLAYERS_IN_TEAM = "Players in team:";

GroupInputDialog::GroupInputDialog(QWidget* parent)
    : QDialog(parent)
{
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
    m_layout->addRow(LABEL_NAME, m_name_line_edit.get());
    m_layout->addRow(LABEL_TEAMS, m_teams_spin_box.get());
    m_layout->addRow(LABEL_PLAYERS_IN_TEAM, m_players_in_team_spin_box.get());
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
        QMessageBox::warning(this, WINDOW_TITLE, ERROR_MESSAGE);
    }
}

bool GroupInputDialog::validateInput() const
{
    return !m_name_line_edit->text().isEmpty();
}
