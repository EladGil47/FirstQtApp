#ifndef FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP
#define FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>

#include <memory>
class GroupInputDialog : public QDialog
{
    Q_OBJECT
public:
    GroupInputDialog(QWidget* parent = nullptr);
    QString getGroupName() const;
    int     getTeamsAmount() const;
    int     getPlayersInTeamAmount() const;

private:
    std::shared_ptr<QLineEdit>        name_line_edit;
    std::shared_ptr<QSpinBox>         players_in_team_spin_box;
    std::shared_ptr<QSpinBox>         teams_spin_box;
    std::shared_ptr<QDialogButtonBox> button_box;
};

#endif // FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP
