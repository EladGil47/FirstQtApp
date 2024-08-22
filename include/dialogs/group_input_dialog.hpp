#ifndef FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP
#define FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
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
    std::shared_ptr<QLineEdit>        m_name_line_edit;
    std::shared_ptr<QSpinBox>         m_players_in_team_spin_box;
    std::shared_ptr<QSpinBox>         m_teams_spin_box;
    std::shared_ptr<QDialogButtonBox> m_button_box;
    std::shared_ptr<QFormLayout>      m_layout;
};

#endif // FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP
