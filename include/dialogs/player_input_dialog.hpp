#ifndef FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP
#define FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLineEdit>

#include <memory>

class PlayerInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlayerInputDialog(QWidget* parent = nullptr);

    QString getPlayerName() const;
    QString getPlayerRole() const;
    double  getPlayerRate() const;

private:
    std::unique_ptr<QLineEdit>        m_name_line_edit;
    std::unique_ptr<QDoubleSpinBox>   m_rate_spin_box;
    std::unique_ptr<QComboBox>        m_role_combo_box;
    std::unique_ptr<QDialogButtonBox> m_button_box;
    std::unique_ptr<QFormLayout>      m_form_layout;

    bool validateInput() const;

    static constexpr const char* WINDOW_TITLE = "Create new player";

private slots:
    void onAccepted();
};

#endif // FIRST_QT_APP_INCLUDE_PLAYER_INPUT_DIALOG_HPP
