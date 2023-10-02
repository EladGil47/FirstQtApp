#ifndef FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H
#define FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H

#include <QWidget>
#include "base_list_manager_window.h"
#include "group.hpp"
#include <memory>
#include <QDialog>

#include "checkable_player_item_widget.hpp"
#include <QPushButton>

#include "app_common.hpp"

class CreateTeamsWindow : public BaseListManagerWindow
{
    Q_OBJECT

public:
    QLabel *m_selected_players_amount_label;
    QLabel *m_slash_label;
    QLabel *m_max_selected_players_amount_label;
    uint32_t m_selected_players_amount = 0;
    uint32_t m_max_selected_players_amount;
    bool m_all_unchecked_disable;
    QPushButton *m_ok_button;
    QPushButton *m_cancel_button;
    std::shared_ptr<Group> m_group;
    std::shared_ptr<PlayersCollection> m_selected_players ;

    void initOkButton()
    {
        m_ok_button = new QPushButton("OK", this);
        m_ok_button->setStyleSheet(Style::GREEN_BUTTON_HOR_LAYOUT);
        connect(m_ok_button, &QPushButton::clicked, this, onOkButtonClicked);
    }

    void initCancelButton()
    {
        m_cancel_button = new QPushButton("Cancel", this);
        m_cancel_button->setStyleSheet(Style::RED_BUTTON_HOR_LAYOUT);
        connect(m_cancel_button, &QPushButton::clicked, this, onCancelButtonClicked);
    }

    void initSelectedPlayersAmountLabel()
    {
        m_selected_players_amount_label = new QLabel(QString::number(m_selected_players_amount));
        m_selected_players_amount_label->setFont(Fonts::LIST_LABEL_FONT);
    }

    void initSlashLabel()
    {
        m_slash_label = new QLabel("/");
        m_slash_label->setFont(Fonts::LIST_LABEL_FONT);
    }

    void initMaxSelectedPlayersAmountLabel(uint16_t max_amount)
    {
        m_max_selected_players_amount_label = new QLabel(QString::number(max_amount));
        m_max_selected_players_amount_label->setFont(Fonts::LIST_LABEL_FONT);
    }

    CreateTeamsWindow(std::shared_ptr<Group> group = nullptr)
    {
        m_selected_players = std::make_shared<PlayersCollection>();

        m_group = group;
        initBaseWindowLayout();
        m_header_label->setEditablity(false);
        setHeaderLabelText(QString::fromStdString(group->getName()));

        setListLabelText();

        initSelectedPlayersAmountLabel();
        m_list_label_layout->addWidget(m_selected_players_amount_label);

        initSlashLabel();
        m_list_label_layout->addWidget(m_slash_label);

        m_max_selected_players_amount = group->getTeamsAmount() * group->getPlayersInTeamAmount();
        initMaxSelectedPlayersAmountLabel(m_max_selected_players_amount);
        m_list_label_layout->addWidget(m_max_selected_players_amount_label);

        QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_list_label_layout->addSpacerItem(spacer);

        setButtonsHorLayout();
        initList();
    }

    void setListLabelText() override
    {
        m_list_label->setText("Checked players :");
    }

    void setButtonsHorLayout() override
    {
        m_buttons_hor_layout->addStretch(1);

        initOkButton();
        m_buttons_hor_layout->addWidget(m_ok_button, 2);

        initCancelButton();
        m_buttons_hor_layout->addWidget(m_cancel_button, 2);
        m_buttons_hor_layout->addStretch(1);
    }

    void addItemToList(std::shared_ptr<Player> player)
    {
        CheckablePlayerItemWidget *player_item_widget = new CheckablePlayerItemWidget(player);
        connect(player_item_widget, CheckablePlayerItemWidget::checkBoxStateChangedSignal, this, onCheckBoxStateChanged);
        QListWidgetItem *item = new QListWidgetItem(m_list_list_widget);
        item->setSizeHint(player_item_widget->sizeHint());
        m_list_list_widget->setItemWidget(item, player_item_widget);
    }

    void initList() override
    {
        for (std::shared_ptr<Player> player : m_group->getPlayersCollectionRef().getCollectionRef())
        {
            addItemToList(player);
        }
    }

signals:
    void cancelButtonClickedSignal(size_t id);
    void okButtonClickedSignal(std::shared_ptr <PlayersCollection> players);

private slots:

    void onCancelButtonClicked()
    {
        emit cancelButtonClickedSignal(m_group->getId());
    }

    void onOkButtonClicked()
    {
        if (m_selected_players->getSize() == m_max_selected_players_amount)
        {
            emit okButtonClickedSignal(m_selected_players);
            // emit okButtonClickedSignal();

        }
        else
        {
            initSelectMorePlayersDialog();
        }
    }

    void initSelectMorePlayersDialog()
    {
        QDialog *dialog = new QDialog;
        dialog->setWindowTitle("Warning");
        dialog->setStyleSheet(Style::OFFWHITE_BACKGROUND);
        dialog->setFixedSize(250, 100);
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *label = new QLabel("Please select more players");
        label->setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);
        dialog->setLayout(layout);
        dialog->exec();
    }

    void disableAllUnchecked()
    {
        m_all_unchecked_disable = true;

        int item_count = m_list_list_widget->count();
        for (int i = 0; i < item_count; ++i)
        {
            QListWidgetItem *item = m_list_list_widget->item(i); // Replace 'row' with the row number you want to retrieve
            if (item)
            {
                CheckablePlayerItemWidget *widget = qobject_cast<CheckablePlayerItemWidget *>(m_list_list_widget->itemWidget(item));
                if (widget)
                {
                    if (widget->getCheckBoxState() != Qt::CheckState::Checked)
                    {
                        widget->setIsCheckBoxEnabled(false);
                    }
                }
            }
        }
    }

    void enableAllCheckables()
    {
        int item_count = m_list_list_widget->count();
        for (int i = 0; i < item_count; ++i)
        {
            QListWidgetItem *item = m_list_list_widget->item(i); // Replace 'row' with the row number you want to retrieve
            if (item)
            {
                CheckablePlayerItemWidget *widget = qobject_cast<CheckablePlayerItemWidget *>(m_list_list_widget->itemWidget(item));
                if (widget)
                {
                    widget->setIsCheckBoxEnabled(true);
                    m_all_unchecked_disable = false;
                }
            }
        }
    }

    void onCheckBoxStateChanged(size_t id, int state)
    {
        switch (state)
        {
        case Qt::CheckState::Unchecked:
        {
            m_selected_players_amount--;
            size_t index = m_selected_players->getIndexById(id);
            m_selected_players->deleteItem(index);
            break;
        }
        case Qt::CheckState::Checked:
        {
            m_selected_players_amount++;
            std::shared_ptr<Player> player = m_group->getPlayersCollection().getItem(id);
            m_selected_players->addItem(player);
            break;
        }
        default:
            break;
        }
        // FOR DEBUG
        // m_selected_players->display();
        //

        m_selected_players_amount_label->setText(QString::number(m_selected_players_amount));
        if (m_selected_players_amount == m_max_selected_players_amount)
        {
            disableAllUnchecked();
        }
        if (m_all_unchecked_disable)
        {
            if (m_selected_players_amount == m_max_selected_players_amount - 1)
            {
                enableAllCheckables();
            }
        }
    }
};

#endif // FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H