#ifndef FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP
#define FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSpinBox>

class GroupInputDialog : public QDialog
{
    Q_OBJECT
public:
    GroupInputDialog(QWidget *parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Create new group");

        name_line_edit = new QLineEdit(this);
        teams_spin_box = new QSpinBox(this);
        teams_spin_box->setRange(2, 4);
        teams_spin_box->setSingleStep(1);

        players_in_team_spin_box = new QSpinBox(this);
        players_in_team_spin_box->setRange(1, 11);
        players_in_team_spin_box->setSingleStep(1);

        QFormLayout *layout = new QFormLayout(this);
        layout->addRow("Name:", name_line_edit);
        layout->addRow("teams:", teams_spin_box);
        layout->addRow("players in team:", players_in_team_spin_box);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &GroupInputDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &GroupInputDialog::reject);
    }

    QString getGroupName() const
    {
        return name_line_edit->text();
    }

    int getTeamsAmount() const
    {
        return teams_spin_box->value();
    }

    int getPlayersInTeamAmount() const
    {
        return players_in_team_spin_box->value();
    }

private:
    QLineEdit *name_line_edit;
    QSpinBox *players_in_team_spin_box;
    QSpinBox *teams_spin_box;
};

#endif // FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP
