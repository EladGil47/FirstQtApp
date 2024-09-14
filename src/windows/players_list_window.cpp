#include "players_list_window.hpp"
#include "app_common.hpp"
#include "message_box_util.hpp"
#include "player_input_dialog.hpp"
#include "player_item_widget.hpp"

PlayersListWindow::PlayersListWindow(std::shared_ptr<Group> group)
{
    if (group)
    {
        m_group = group;

        initGroupNameLabel();
        initPlayersList();
        initButtonsHorLayout();

        setupLayout();
    }
}

void PlayersListWindow::initPlayersList()
{
    m_players_list = new LabeledListWidget();
    m_players_list->setListColor(Style::LIST);
    initPlayersAmountLabel();
    initList();
}

void PlayersListWindow::initGroupNameLabel()
{
    auto m_header_label_text = QString::fromStdString(m_group->getName());
    auto label               = std::make_shared<QLabel>(m_header_label_text);
    label->setFont(Fonts::HEADER_LABEL_FONT);
    label->setAlignment(Qt::AlignHCenter);
    m_group_label_name = new EditableLabel(label);
    connect(m_group_label_name, &EditableLabel::finishEditingSig, this, &PlayersListWindow::setGroupName);
}

void PlayersListWindow::initPlayersAmountLabel()
{
    QLabel* players_text_label = new QLabel("Players :");
    m_players_list->addWidgetAboveList(players_text_label);

    m_players_amount_label = new QLabel;
    initPlayersAmountLabelText();
    m_players_amount_label->setFont(Fonts::LIST_LABEL_FONT);
    m_players_list->addWidgetAboveList(m_players_amount_label);

    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_players_list->addSpacerAboveList(spacer);
}

void PlayersListWindow::initPlayersAmountLabelText()
{
    QString size = QString::number(m_group->getNumOfPlayers());
    m_players_amount_label->setText(size);
}

void PlayersListWindow::onPlayerNameChanged(uint16_t id, const std::string& name)
{
    m_group->setNameById(id, name);
}

void PlayersListWindow::onPlayerRateChanged(uint16_t id, double rate)
{
    m_group->setRateById(id, rate);
}

void PlayersListWindow::setGroupName(const QString& text)
{
    m_group->setName(text.toStdString());
}

void PlayersListWindow::initList()
{
    for (std::shared_ptr<Player> player : m_group->getPlayersCollection().getCollection())
    {
        addItemToList(player);
    }
}

void PlayersListWindow::initCreateNewPlayerButton()
{
    m_create_new_player_button = new QPushButton("Create new player", this);
    m_create_new_player_button->setStyleSheet(ui_settings::BOTTOM_BUTTONS_LINE_COLOR);
    connect(m_create_new_player_button, &QPushButton::clicked, this, &PlayersListWindow::onCreateNewPlayerButton);
}

void PlayersListWindow::initCreateTeamsButton()
{
    m_create_teams_button = new QPushButton("Create teams", this);
    m_create_teams_button->setStyleSheet(ui_settings::BOTTOM_BUTTONS_LINE_COLOR);
    connect(m_create_teams_button, &QPushButton::clicked, this, &PlayersListWindow::onCreateTeamsClicked);
}

void PlayersListWindow::initGoBackButton()
{
    m_go_back_button = new QPushButton("Go back", this);
    m_go_back_button->setStyleSheet(ui_settings::BOTTOM_BUTTONS_LINE_COLOR);
    connect(m_go_back_button, &QPushButton::clicked, this, &PlayersListWindow::onGoBackButton);
}

void PlayersListWindow::initButtonsHorLayout()
{
    m_buttons_hor_layout = new QHBoxLayout;
    m_buttons_hor_layout->addStretch(1);

    initCreateNewPlayerButton();
    addButtonToButtonsHorLayout(m_create_new_player_button);

    initCreateTeamsButton();
    addButtonToButtonsHorLayout(m_create_teams_button);

    initGoBackButton();
    addButtonToButtonsHorLayout(m_go_back_button);

    m_buttons_hor_layout->addStretch(1);
}

void PlayersListWindow::addButtonToButtonsHorLayout(QPushButton* button)
{
    if (button)
        m_buttons_hor_layout->addWidget(button, 2);
    else
        qDebug() << "Notice : The system prevent to add unassigned button to a layout";
}

void PlayersListWindow::setupLayout()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_group_label_name);
    layout->addWidget(m_players_list);
    layout->addLayout(m_buttons_hor_layout);
}

// Slots :

void PlayersListWindow::onCreateNewPlayerButton()
{
    PlayerInputDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        QString name = dialog.getPlayerName();
        double  rate = dialog.getPlayerRate();
        QString role = dialog.getPlayerRole();

        Player::Config config;
        config.name = name.toStdString();
        config.rate = rate;
        config.role = Player::toPlayerRole(role.toStdString());
        config.id   = static_cast<uint16_t>(m_group->getNumOfPlayers());

        std::shared_ptr<Player> new_player = std::make_shared<Player>(config);
        m_group->addPlayerToCollection(new_player);
        addItemToList(new_player);
        initPlayersAmountLabelText();
    }
}

enum CreateTeamsOption
{
    RANDOM,
    MANUALLY
};

CreateTeamsOption showDialogWithOptions()
{
    CreateTeamsOption option;
    QMessageBox       dialog;
    dialog.setWindowTitle("Kohot");
    dialog.setText("Choose an option:");
    dialog.setIcon(QMessageBox::Question);
    dialog.setStyleSheet(ui_settings::MESSAGES_BOX_COLOR);
    dialog.setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);

    QPushButton* manual_button = dialog.addButton("Manually", QMessageBox::ActionRole);
    QPushButton* random_button = dialog.addButton("Random", QMessageBox::ActionRole);

    QObject::connect(manual_button, &QPushButton::clicked, [&]() {
        option = CreateTeamsOption::MANUALLY;
    });

    QObject::connect(random_button, &QPushButton::clicked, [&]() {
        option = CreateTeamsOption::RANDOM;
    });

    dialog.exec();

    return option;
}

void PlayersListWindow::onCreateTeamsClicked()
{
    uint16_t minimun_required_players_amount = m_group->getPlayersInTeamAmount() * m_group->getTeamsAmount();
    uint16_t players_amount                  = static_cast<uint16_t>(m_group->getNumOfPlayers());

    if (players_amount >= minimun_required_players_amount)
    {
        CreateTeamsOption option;
        option = showDialogWithOptions();
        if (option == CreateTeamsOption::RANDOM)
        {
            emit setToCreateTeamsWindowSignal(m_group->getId());
        }
        else if (option == CreateTeamsOption::MANUALLY)
        {
            std::shared_ptr<PlayersCollection> players = std::make_shared<PlayersCollection>();

            emit setToDisplayTeamsWindowSignal(players, m_group->getId());
        }
    }
    else
    {
        uint16_t required_players_to_add = minimun_required_players_amount - players_amount;
        QString  message                 = "Please add " + QString::number(required_players_to_add) + " more players to create teams";
        MessageBoxUtil::show(message, MessageBoxUtil::Type::Warning);
    }
}

void PlayersListWindow::addItemToList(std::shared_ptr<Player> player)
{
    PlayerItemWidget* player_item_widget = new PlayerItemWidget(player);
    connect(player_item_widget, &PlayerItemWidget::enterButtonClickedSignal, this, &PlayersListWindow::onEnterButton);
    connect(player_item_widget, &PlayerItemWidget::removeButtonClickedSignal, this, &PlayersListWindow::onRemoveButton);
    connect(player_item_widget, &PlayerItemWidget::playerNameChangedSignal, this, &PlayersListWindow::onPlayerNameChanged);
    connect(player_item_widget, &PlayerItemWidget::playerRateChangedSignal, this, &PlayersListWindow::onPlayerRateChanged);

    m_players_list->addItemToList(player_item_widget);
}

void PlayersListWindow::onRemoveButton(size_t id)
{
    m_group->deletePlayerFromCollectionById(id);
    QListWidgetItem* itemToRemove = m_players_list->m_list->takeItem(id);
    delete itemToRemove;
    for (size_t index = id; index < m_group->getNumOfPlayers(); index++)
    {
        m_group->setIdById(index, static_cast<uint16_t>(index));
    }
    m_players_list->removeAllItemsFromList();
    initList();
    initPlayersAmountLabelText();
}

void PlayersListWindow::onEnterButton(size_t id)
{
    qDebug() << "hello" << id;
    /// Open a window with player attributes
    /// Calls team creator
}

void PlayersListWindow::onGoBackButton()
{
    emit onGoBackButtonClickedSignal();
}