#include "group_input_dialog.hpp"

#include "resource_paths.hpp"
#include "static_settings.hpp"

namespace
{
static constexpr const char* WINDOW_TITLE          = "Create new group";
static constexpr const char* LABEL_NAME            = "Name:";
static constexpr const char* LABEL_TEAMS           = "Teams:";
static constexpr const char* LABEL_PLAYERS_IN_TEAM = "Players in team:";
} // namespace

GroupInputDialog::GroupInputDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(WINDOW_TITLE);

    m_name_line_edit = std::make_shared<QLineEdit>(this);

    m_teams_spin_box = std::make_shared<QSpinBox>(this);
    int teamsMin     = StaticSettings::team_range[0];
    int teamsMax     = StaticSettings::team_range[1];
    m_teams_spin_box->setRange(teamsMin, teamsMax);

    m_players_in_team_spin_box = std::make_shared<QSpinBox>(this);
    int playersMin             = StaticSettings::players_in_team_range[0];
    int playersMax             = StaticSettings::players_in_team_range[1];
    m_players_in_team_spin_box->setRange(playersMin, playersMax);

    m_button_box = std::make_shared<QDialogButtonBox>(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    m_layout = std::make_shared<QFormLayout>(this);
    m_layout->addRow(LABEL_NAME, m_name_line_edit.get());
    m_layout->addRow(LABEL_TEAMS, m_teams_spin_box.get());
    m_layout->addRow(LABEL_PLAYERS_IN_TEAM, m_players_in_team_spin_box.get());
    m_layout->addWidget(m_button_box.get());

    connect(m_button_box.get(), &QDialogButtonBox::accepted, this, &GroupInputDialog::accept);
    connect(m_button_box.get(), &QDialogButtonBox::rejected, this, &GroupInputDialog::reject);
}

QString GroupInputDialog::getGroupName() const
{
    return m_name_line_edit->text();
}

int GroupInputDialog::getTeamsAmount() const
{
    return m_teams_spin_box->value();
}

int GroupInputDialog::getPlayersInTeamAmount() const
{
    return m_players_in_team_spin_box->value();
}
