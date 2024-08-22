#include "group_input_dialog.hpp"

#include <QFormLayout>

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

    name_line_edit = std::make_shared<QLineEdit>(this);
    teams_spin_box = std::make_shared<QSpinBox>(this);
    teams_spin_box->setRange(2, 4);
    teams_spin_box->setSingleStep(1);

    players_in_team_spin_box = std::make_shared<QSpinBox>(this);
    players_in_team_spin_box->setRange(1, 11);
    players_in_team_spin_box->setSingleStep(1);

    QFormLayout* layout = new QFormLayout(this);
    layout->addRow(LABEL_NAME, name_line_edit.get());
    layout->addRow(LABEL_TEAMS, teams_spin_box.get());
    layout->addRow(LABEL_PLAYERS_IN_TEAM, players_in_team_spin_box.get());

    button_box = std::make_shared<QDialogButtonBox>(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(button_box.get());

    connect(button_box.get(), &QDialogButtonBox::accepted, this, &GroupInputDialog::accept);
    connect(button_box.get(), &QDialogButtonBox::rejected, this, &GroupInputDialog::reject);
}

QString GroupInputDialog::getGroupName() const
{
    return name_line_edit->text();
}

int GroupInputDialog::getTeamsAmount() const
{
    return teams_spin_box->value();
}

int GroupInputDialog::getPlayersInTeamAmount() const
{
    return players_in_team_spin_box->value();
}
