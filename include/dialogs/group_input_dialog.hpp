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
    int32_t getTeamsAmount() const;
    int32_t getPlayersInTeamAmount() const;

private:
    std::unique_ptr<QLineEdit> m_name_line_edit;
    std::unique_ptr<QSpinBox>  m_teams_spin_box;
    std::unique_ptr<QSpinBox>  m_players_in_team_spin_box;

    std::unique_ptr<QDialogButtonBox> m_button_box;
    std::unique_ptr<QFormLayout>      m_form_layout;

    bool validateInput() const;

    static constexpr const char* WINDOW_TITLE = "Create new group";

private slots:
    void onAccepted();
};

#endif // FIRST_QT_APP_INCLUDE_GROUP_INPUT_DIALOG_HPP
