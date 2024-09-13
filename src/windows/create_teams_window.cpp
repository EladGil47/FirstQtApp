#include "create_teams_window.hpp"

CreateTeamsWindow::CreateTeamsWindow(std::shared_ptr<Group> group)
{
    if (group)
    {
        m_group                       = group;
        m_selected_players            = std::make_shared<PlayersCollection>();
        m_max_selected_players_amount = group->getTeamsAmount() * group->getPlayersInTeamAmount();

        initHeaderLabel();
        initListsLayout();
        initButtonsHorLayout();

        setupLayout();
    }
}

void CreateTeamsWindow::initHeaderLabel()
{
    m_header_label = new QLabel(QString::fromStdString(m_group->getName()));
    m_header_label->setFont(Fonts::HEADER_LABEL_FONT);
    m_header_label->setAlignment(Qt::AlignHCenter);
}

void CreateTeamsWindow::initOkButton()
{
    m_ok_button = new QPushButton("OK");
    m_ok_button->setStyleSheet(Style::GREEN_BUTTON_HOR_LAYOUT);
    connect(m_ok_button, &QPushButton::clicked, this, &CreateTeamsWindow::onOkButtonClicked);
}

void CreateTeamsWindow::initCancelButton()
{
    m_cancel_button = new QPushButton("Cancel");
    m_cancel_button->setStyleSheet(Style::RED_BUTTON_HOR_LAYOUT);
    connect(m_cancel_button, &QPushButton::clicked, this, &CreateTeamsWindow::onCancelButtonClicked);
}

void CreateTeamsWindow::initCheckedPlayersList()
{
    QLabel* m_coming_players_label = new QLabel("Coming players");

    m_checked_players_list = new LabeledListWidget();
    m_checked_players_list->setListColor(Style::LIST);
    m_checked_players_list->addWidgetAboveList(m_coming_players_label);
}

void CreateTeamsWindow::initCheckablePlayersList()
{
    QLabel* checked_label = new QLabel("Checked :");

    m_selected_players_amount_label = new QLabel(QString::number(m_selected_players_amount));

    QLabel* slash_label = new QLabel("/");

    QLabel* max_selected_players_amount_label = new QLabel(QString::number(m_max_selected_players_amount));

    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    random_label = new QLabel("Auto fill");

    m_random_select_check_box = new QCheckBox;
    m_random_select_check_box->setToolTip("Press to Auto fill");
    m_random_select_check_box->setStyleSheet(
        "QCheckBox::indicator {"
        "    border-color: black;"
        "    border-radius: 12px;" // Make it circular
        "    background-color: yellow;"
        "    width: 24px;"
        "    height: 24px;"
        "}"
        "QCheckBox::indicator:checked {"
        "   background-color: red;" // Green color when checked
        "}");
    connect(m_random_select_check_box, &QCheckBox::stateChanged, this, &CreateTeamsWindow::onRandomSelectCheckBoxStateChanged);

    m_checkable_players_list = new LabeledListWidget();
    m_checkable_players_list->setListColor(Style::LIST);
    m_checkable_players_list->addWidgetAboveList(m_random_select_check_box);
    m_checkable_players_list->addWidgetAboveList(random_label);
    m_checkable_players_list->addSpacerAboveList(spacer);
    m_checkable_players_list->addWidgetAboveList(checked_label);
    m_checkable_players_list->addWidgetAboveList(m_selected_players_amount_label);
    m_checkable_players_list->addWidgetAboveList(slash_label);
    m_checkable_players_list->addWidgetAboveList(max_selected_players_amount_label);
    addAllPlayersToCheckablePlayersList();
}

void CreateTeamsWindow::setupLayout()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_header_label);
    layout->addLayout(m_lists_layout);
    layout->addLayout(m_buttons_hor_layout);
}

void CreateTeamsWindow::initListsLayout()
{
    m_lists_layout = new QHBoxLayout;

    initCheckablePlayersList();
    initCheckedPlayersList();

    m_lists_layout->addWidget(m_checkable_players_list);
    m_lists_layout->addWidget(m_checked_players_list);
}

void CreateTeamsWindow::initButtonsHorLayout()
{
    m_buttons_hor_layout = new QHBoxLayout;

    m_buttons_hor_layout->addStretch(1);

    initOkButton();
    m_buttons_hor_layout->addWidget(m_ok_button, 2);

    initCancelButton();
    m_buttons_hor_layout->addWidget(m_cancel_button, 2);
    m_buttons_hor_layout->addStretch(1);
}

void CreateTeamsWindow::addPlayerToCheckablePlayersList(std::shared_ptr<Player> player)
{
    CheckablePlayerItemWidget* player_item_widget = new CheckablePlayerItemWidget(player);
    connect(player_item_widget, &CheckablePlayerItemWidget::checkBoxStateChangedSignal, this, &CreateTeamsWindow::onCheckBoxStateChanged);
    m_checkable_players_list->addItemToList(player_item_widget);
}

void CreateTeamsWindow::addPlayerToCheckedPlayersList(std::shared_ptr<Player> player)
{
    BasePlayerItemWidget* player_item_widget = new BasePlayerItemWidget(player);
    player_item_widget->setupLayout(
        (BasePlayerItemWidget::SetupLayoutOptions::NAME |
            BasePlayerItemWidget::SetupLayoutOptions::REMOVE));
    connect(player_item_widget, &BasePlayerItemWidget::removeButtonClickedSignal, this, &CreateTeamsWindow::onRemovePlayerButton);
    m_checked_players_list->addItemToList(player_item_widget);
}

void CreateTeamsWindow::addAllPlayersToCheckablePlayersList()
{
    for (std::shared_ptr<Player> player : m_group->getPlayersCollection().getCollection())
    {
        addPlayerToCheckablePlayersList(player);
    }
}

void CreateTeamsWindow::disableAllUnchecked()
{
    m_all_unchecked_disable = true;

    int item_count = m_checkable_players_list->m_list->count();
    for (int i = 0; i < item_count; ++i)
    {
        QListWidgetItem* item = m_checkable_players_list->m_list->item(i); // Replace 'row' with the row number you want to retrieve
        if (item)
        {
            CheckablePlayerItemWidget* widget = qobject_cast<CheckablePlayerItemWidget*>(m_checkable_players_list->m_list->itemWidget(item));
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

void CreateTeamsWindow::setCheckableItemWidgetCheckBox(size_t index, Qt::CheckState state)
{
    QListWidgetItem* item = m_checkable_players_list->m_list->item(index); // Replace 'row' with the row number you want to retrieve
    if (item)
    {
        CheckablePlayerItemWidget* widget = qobject_cast<CheckablePlayerItemWidget*>(m_checkable_players_list->m_list->itemWidget(item));
        if (widget)
        {
            widget->setCheckState(state);
        }
    }
}

void CreateTeamsWindow::enableAllCheckables()
{
    int item_count = m_checkable_players_list->m_list->count();
    for (int i = 0; i < item_count; ++i)
    {
        QListWidgetItem* item = m_checkable_players_list->m_list->item(i); // Replace 'row' with the row number you want to retrieve
        if (item)
        {
            CheckablePlayerItemWidget* widget = qobject_cast<CheckablePlayerItemWidget*>(m_checkable_players_list->m_list->itemWidget(item));
            if (widget)
            {
                widget->setIsCheckBoxEnabled(true);
                m_all_unchecked_disable = false;
            }
        }
    }
}

void CreateTeamsWindow::removePlayerFromCheckedPlayerList(size_t id)
{
    int       item_count = m_checked_players_list->m_list->count();
    int const FIRST_ROW  = 0;
    for (int i = FIRST_ROW; i < item_count; ++i)
    {
        QListWidgetItem* item = m_checked_players_list->m_list->item(i); // Replace 'row' with the row number you want to retrieve
        if (item)
        {
            BasePlayerItemWidget* widget = qobject_cast<BasePlayerItemWidget*>(m_checked_players_list->m_list->itemWidget(item));
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

void CreateTeamsWindow::uncheckAll()
{
    for (std::shared_ptr<Player> player : m_selected_players->getCollection())
    {
        setCheckableItemWidgetCheckBox(player->getId(), Qt::CheckState::Unchecked);
    }
}

void CreateTeamsWindow::onRemovePlayerButton(size_t player_id)
{
    setCheckableItemWidgetCheckBox(player_id, Qt::CheckState::Unchecked);
}

void CreateTeamsWindow::onCancelButtonClicked()
{
    emit cancelButtonClickedSignal(m_group->getId());
}

void CreateTeamsWindow::onOkButtonClicked()
{
    if (m_selected_players->getSize() == m_max_selected_players_amount)
    {
        emit okButtonClickedSignal(m_selected_players, m_group->getId());
    }
    else
    {
        static constexpr const char* MESSAGE = "Please select more players";
        MessageBoxUtil::show(MESSAGE, MessageBoxUtil::Type::Warning);
    }
}

void CreateTeamsWindow::onCheckBoxStateChanged(size_t id, int state)
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
            if (m_selected_players_amount == m_max_selected_players_amount)
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

void CreateTeamsWindow::onRandomSelectCheckBoxStateChanged(int state)
{
    switch (state)
    {
        case Qt::CheckState::Unchecked:
        {
            if (m_selected_players_amount == m_max_selected_players_amount)
            {
                uncheckAll();
            }
            random_label->setText("Auto fill");
            m_random_select_check_box->setToolTip("Press to Auto fill");
            break;
        }
        case Qt::CheckState::Checked:
        {
            random_label->setText("Reset");
            m_random_select_check_box->setToolTip("Press to Reset");

            std::random_device                 rd;
            std::mt19937                       gen(rd());
            std::uniform_int_distribution<int> distribution(0, m_group->getNumOfPlayers() - 1);
            std::set<int>                      generatedNumbers;
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
            break;
        }
        default:
            break;
    }
}
