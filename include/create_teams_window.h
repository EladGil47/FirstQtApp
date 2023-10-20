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

#include "labeled_list_widget.hpp"

#include <random>
#include <set>

#include <QMessageBox>
class CreateTeamsWindow : public QWidget
{
    Q_OBJECT

public:
    CreateTeamsWindow(std::shared_ptr<Group> group)
    {
        if (group)
        {
            m_group = group;
            m_selected_players = std::make_shared<PlayersCollection>();
            m_max_selected_players_amount = group->getTeamsAmount() * group->getPlayersInTeamAmount();


            initHeaderLabel();
            initListsLayout();
            initButtonsHorLayout();

            setupLayout();
        }
    }

    void initHeaderLabel()
    {
        m_header_label = new QLabel(QString::fromStdString(m_group->getName()));
        m_header_label->setFont(Fonts::HEADER_LABEL_FONT);
        m_header_label->setAlignment(Qt::AlignHCenter);
    }

    void initOkButton()
    {
        m_ok_button = new QPushButton("OK");
        m_ok_button->setStyleSheet(Style::GREEN_BUTTON_HOR_LAYOUT);
        connect(m_ok_button, &QPushButton::clicked, this, &CreateTeamsWindow::onOkButtonClicked);
    }

    void initCancelButton()
    {
        m_cancel_button = new QPushButton("Cancel");
        m_cancel_button->setStyleSheet(Style::RED_BUTTON_HOR_LAYOUT);
        connect(m_cancel_button, &QPushButton::clicked, this, &CreateTeamsWindow::onCancelButtonClicked);
    }
    
    void initCheckedPlayersList()
    {
        m_checked_players_list = new LabeledListWidget();
        m_checked_players_list->setListColor(Style::LIST);
        QLabel *m_list_label = new QLabel("Coming players :");
        m_checked_players_list->addWidgetAboveList(m_list_label);


    }

    void initCheckablePlayersList()
    {
        m_checkable_players_list = new LabeledListWidget();
        m_checkable_players_list->setListColor(Style::LIST);
        
        QLabel *m_list_label = new QLabel("Checked players :");
        m_checkable_players_list->addWidgetAboveList(m_list_label);
        
        m_selected_players_amount_label = new QLabel(QString::number(m_selected_players_amount));
        m_checkable_players_list->addWidgetAboveList(m_selected_players_amount_label);
        
        QLabel *m_slash_label = new QLabel("/");
        m_checkable_players_list->addWidgetAboveList(m_slash_label);
        
        QLabel * m_max_selected_players_amount_label = new QLabel(QString::number(m_max_selected_players_amount));
        m_checkable_players_list->addWidgetAboveList(m_max_selected_players_amount_label);
        
        QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_checkable_players_list->addSpacerAboveList(spacer);

        
        random_label = new QLabel("Auto fill :");
        m_checkable_players_list->addWidgetAboveList(random_label);

        m_random_select_check_box = new QCheckBox;
        m_random_select_check_box->setToolTip("Press to Auto fill");
        m_random_select_check_box->setStyleSheet(
         "QCheckBox::indicator {"
                           "    border-color: black;"
                           "    border-radius: 12px;"    // Make it circular
                           "    background-color: yellow;"
                           "    width: 24px;"
                           "    height: 24px;"
                           "}"
                           "QCheckBox::indicator:checked {"
                           "   background-color: red;"  // Green color when checked
                           "}");
        connect(m_random_select_check_box, &QCheckBox::stateChanged, this, &CreateTeamsWindow::onRandomSelectCheckBoxStateChanged);
        m_checkable_players_list->addWidgetAboveList(m_random_select_check_box);


        addAllPlayersToCheckablePlayersList();
    }

    void setupLayout()
    {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(m_header_label);
        layout->addLayout(m_lists_layout);
        layout->addLayout(m_buttons_hor_layout);
    }

    void initListsLayout()
    {
        m_lists_layout = new QHBoxLayout;

        initCheckablePlayersList();
        initCheckedPlayersList();

        m_lists_layout->addWidget(m_checkable_players_list);
        m_lists_layout->addWidget(m_checked_players_list);

    }

    void initButtonsHorLayout() 
    {
        m_buttons_hor_layout = new QHBoxLayout;

        m_buttons_hor_layout->addStretch(1);

        initOkButton();
        m_buttons_hor_layout->addWidget(m_ok_button, 2);

        initCancelButton();
        m_buttons_hor_layout->addWidget(m_cancel_button, 2);
        m_buttons_hor_layout->addStretch(1);
    }

    void addPlayerToCheckablePlayersList(std::shared_ptr<Player> player)
    {
        CheckablePlayerItemWidget *player_item_widget = new CheckablePlayerItemWidget(player);
        connect(player_item_widget, &CheckablePlayerItemWidget::checkBoxStateChangedSignal, this, &CreateTeamsWindow::onCheckBoxStateChanged);
        m_checkable_players_list->addItemToList(player_item_widget);
    }

    void addPlayerToCheckedPlayersList(std::shared_ptr<Player> player)
    {
        BasePlayerItemWidget *player_item_widget = new BasePlayerItemWidget(player);
        player_item_widget->setupLayout(BasePlayerItemWidget::SetupLayoutOptions::NAME);
        m_checked_players_list->addItemToList(player_item_widget);
    }

    void addAllPlayersToCheckablePlayersList() 
    {
        for (std::shared_ptr<Player> player : m_group->getPlayersCollectionRef().getCollectionRef())
        {
            addPlayerToCheckablePlayersList(player);
        }
    }

private:
    QLabel *m_header_label ;
    QHBoxLayout *m_lists_layout;
    LabeledListWidget * m_checkable_players_list;
    LabeledListWidget * m_checked_players_list;
    QHBoxLayout *m_buttons_hor_layout;

    QLabel *m_selected_players_amount_label;
    uint32_t m_selected_players_amount = 0;
    uint32_t m_max_selected_players_amount;
    bool m_all_unchecked_disable;
    QPushButton *m_ok_button;
    QPushButton *m_cancel_button;
    std::shared_ptr<Group> m_group;
    std::shared_ptr<PlayersCollection> m_selected_players ;
    QLabel *random_label;
    QCheckBox * m_random_select_check_box;

    void initSelectMorePlayersMessageBox()
    {
        QMessageBox message_box;
        message_box.setWindowTitle("Warning");
        message_box.setIcon(QMessageBox::Warning);
        message_box.setStyleSheet(Settings::MESSAGES_BOX_COLOR);
        message_box.setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
        message_box.setText("Please select more players");
        message_box.setStandardButtons(QMessageBox::Ok);

        message_box.exec();
    }

    void disableAllUnchecked()
    {
        m_all_unchecked_disable = true;

        int item_count = m_checkable_players_list->m_list->count();
        for (int i = 0; i < item_count; ++i)
        {
            QListWidgetItem *item =  m_checkable_players_list->m_list->item(i); // Replace 'row' with the row number you want to retrieve
            if (item)
            {
                CheckablePlayerItemWidget *widget = qobject_cast<CheckablePlayerItemWidget *>(m_checkable_players_list->m_list->itemWidget(item));
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

    void setCheckableItemWidgetCheckBox(size_t index,Qt::CheckState state)
    {
        QListWidgetItem *item = m_checkable_players_list->m_list->item(index); // Replace 'row' with the row number you want to retrieve
        if (item)
        {
            CheckablePlayerItemWidget *widget = qobject_cast<CheckablePlayerItemWidget *>(m_checkable_players_list->m_list->itemWidget(item));
            if (widget)
            {
                    widget->setCheckState(state);
            }
        }
    }

    void enableAllCheckables()
    {
        int item_count = m_checkable_players_list->m_list->count();
        for (int i = 0; i < item_count; ++i)
        {
            QListWidgetItem *item = m_checkable_players_list->m_list->item(i); // Replace 'row' with the row number you want to retrieve
            if (item)
            {
                CheckablePlayerItemWidget *widget = qobject_cast<CheckablePlayerItemWidget *>(m_checkable_players_list->m_list->itemWidget(item));
                if (widget)
                {
                    widget->setIsCheckBoxEnabled(true);
                    m_all_unchecked_disable = false;
                }
            }
        }
    }

    void removePlayerFromCheckedPlayerList(size_t id)
    {
        int item_count = m_checked_players_list->m_list->count();
        int const FIRST_ROW = 0;
        for (int i = FIRST_ROW; i < item_count; ++i)
        {
            QListWidgetItem *item = m_checked_players_list->m_list->item(i); // Replace 'row' with the row number you want to retrieve
            if (item)
            {
                BasePlayerItemWidget *widget = qobject_cast<BasePlayerItemWidget *>(m_checked_players_list->m_list->itemWidget(item));
                if (widget)
                {
                    if (widget->getPlayer()->getId() == id)
                    {
                        m_checked_players_list->m_list->removeItemWidget(item);
                        delete item;
                        delete widget;
                    }
                }
            }
        }
    }
    
    void uncheckAll()
    {
        for (std::shared_ptr<Player> player : m_selected_players->getCollection())
        {
            setCheckableItemWidgetCheckBox(player->getId(), Qt::CheckState::Unchecked);
        }
    }

signals:
    void cancelButtonClickedSignal(size_t id);
    void okButtonClickedSignal(std::shared_ptr <PlayersCollection> players,size_t id);

public slots:

    void onCancelButtonClicked()
    {
        emit cancelButtonClickedSignal(m_group->getId());
    }

    void onOkButtonClicked()
    {
        if (m_selected_players->getSize() == m_max_selected_players_amount)
        {
            emit okButtonClickedSignal(m_selected_players,m_group->getId());
        }
        else
        {
            initSelectMorePlayersMessageBox();
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
            removePlayerFromCheckedPlayerList(id);
            m_random_select_check_box->setCheckState(Qt::CheckState::Unchecked);

            
            break;
        }
        case Qt::CheckState::Checked:
        {
            m_selected_players_amount++;
            std::shared_ptr<Player> player = m_group->getPlayersCollection().getItem(id);
            m_selected_players->addItem(player);
            addPlayerToCheckedPlayersList(player);
            if(m_selected_players_amount == m_max_selected_players_amount)
            {
                m_random_select_check_box->setChecked(true);
            }

            break;
        }
        default:
            break;
        }
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


    void onRandomSelectCheckBoxStateChanged(int state)
    {
        switch (state)
        {
        case Qt::CheckState::Unchecked:
        {
            if (m_selected_players_amount == m_max_selected_players_amount)
            {
                random_label->setText("Auto fill :");
                m_random_select_check_box->setToolTip("Press to Auto fill");
                uncheckAll();
            }
            break;
        }
        case Qt::CheckState::Checked:
        {
            if (m_selected_players_amount != m_max_selected_players_amount)
            {
                random_label->setText("Reset :");
                m_random_select_check_box->setToolTip("Press to Reset");

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> distribution(0, m_group->getNumOfPlayers() - 1);
                std::set<int> generatedNumbers;
                for (std::shared_ptr<Player> player : m_selected_players->getCollection())
                {
                    generatedNumbers.insert(player->getId());
                }
                uint32_t amount_of_players_to_add = m_max_selected_players_amount - m_selected_players_amount;
                for (uint32_t i = 0; i < amount_of_players_to_add; ++i)
                {
                    int randomInt;
                    do
                    {
                        randomInt = distribution(gen);
                        setCheckableItemWidgetCheckBox(randomInt, Qt::CheckState::Checked);

                    } while (generatedNumbers.count(randomInt) > 0);

                    generatedNumbers.insert(randomInt);
                }
            }
            break;
        }
        default:
            break;
        }
    }
};

#endif // FIRST_QT_APP_INCLUDE_CREATE_TEAMS_WINDOW_H 