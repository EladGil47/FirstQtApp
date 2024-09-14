#include "groups_list_window.hpp"

#include <QPixmap>
#include "group_input_dialog.hpp"
#include "group_item_widget.hpp"
#include "resource_paths.hpp"

#include "app_common.hpp"

GroupsListWindow::GroupsListWindow(std::shared_ptr<GroupsCollection> groups_collection)
    : m_groups_collection(groups_collection),
      m_app_name_hor_layout(std::make_unique<QHBoxLayout>()),
      m_groups_list(std::make_unique<LabeledListWidget>()),
      m_create_new_group_button(std::make_unique<QPushButton>(CREATE_NEW_GROUP_BUTTON_TEXT)),
      m_buttons_hor_layout(std::make_unique<QHBoxLayout>())

{
    if (m_groups_collection)
    {
        initAppHorLayout();
        initGroupsList();
        setupButtonsHorLayout();

        setupLayout();
    }
}

void GroupsListWindow::setupLayout()
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(m_app_name_hor_layout.get());
    layout->addWidget(m_groups_list.get());
    layout->addLayout(m_buttons_hor_layout.get());
}

void GroupsListWindow::initAppHorLayout()
{
    m_app_name_hor_layout->addStretch(1);

    QPixmap pixmap(resources_path::SOCCER_BALL);
    int     width  = 30;
    int     height = 30;
    pixmap         = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto left_soccer_ball_label = new QLabel;
    left_soccer_ball_label->setPixmap(pixmap);
    m_app_name_hor_layout->addWidget(left_soccer_ball_label);

    initAppNameLabel();
    m_app_name_hor_layout->addWidget(m_app_name_label.get());

    auto right_soccer_ball_label = new QLabel;
    right_soccer_ball_label->setPixmap(pixmap);
    m_app_name_hor_layout->addWidget(right_soccer_ball_label);

    m_app_name_hor_layout->addStretch(1);
}

void GroupsListWindow::initAppNameLabel()
{
    static constexpr const char* WELCOME_MSG = "Welcome To Kohot";

    auto label = std::make_shared<QLabel>(WELCOME_MSG);
    label->setFont(Fonts::HEADER_LABEL_FONT);
    label->setAlignment(Qt::AlignHCenter);
    m_app_name_label = std::make_unique<EditableLabel>(label);
    m_app_name_label->setEditability(false);
}

void GroupsListWindow::initGroupsList()
{
    initGroupsAmountLabel();
    initList();
}

GroupsListWindow::~GroupsListWindow()
{
}

void GroupsListWindow::initGroupsAmountLabel()
{
    static constexpr const char* GROUPS_LABEL_TEXT = "Groups :";

    auto groups_label     = new QLabel(GROUPS_LABEL_TEXT);
    auto groups_amount    = QString::number(m_groups_collection->getSize());
    m_groups_amount_label = std::make_unique<QLabel>(groups_amount);
    auto spacer           = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_groups_list->addWidgetAboveList(groups_label);
    m_groups_list->addWidgetAboveList(m_groups_amount_label.get());
    m_groups_list->addSpacerAboveList(spacer);
}

void GroupsListWindow::updateGroupsAmountLabel()
{
    QString groups_amount = QString::number(m_groups_collection->getSize());
    m_groups_amount_label->setText(groups_amount);
}

void GroupsListWindow::initCreateNewGroupButton()
{
    m_create_new_group_button->setStyleSheet(Style::DARK_BROWN_BUTTON_HOR_LAYOUT);
    m_create_new_group_button->setToolTip("Click here to create a new group");
    connect(m_create_new_group_button.get(), &QPushButton::clicked, this, &GroupsListWindow::onCreateNewGroupButton);
}

void GroupsListWindow::initList()
{
    for (std::shared_ptr<Group> group : m_groups_collection->getCollection())
    {
        addGroupItemToList(group);
    }
}

void GroupsListWindow::changeGroupName(uint16_t id, const std::string& name)
{
    m_groups_collection->getItem(static_cast<size_t>(id))->setName(name);
}

void GroupsListWindow::addGroupItemToList(std::shared_ptr<Group> group)
{
    GroupItemWidget* group_item_widget = new GroupItemWidget(group);
    connect(group_item_widget, &GroupItemWidget::enterButtonClickedSignal, this, &GroupsListWindow::onEnterGroupButton);
    connect(group_item_widget, &GroupItemWidget::removeButtonClickedSignal, this, &GroupsListWindow::onRemoveGroupButton);
    connect(group_item_widget, &GroupItemWidget::createTeamsButtonClickedSignal, this, &GroupsListWindow::onCreateTeamsButton);
    connect(group_item_widget, &GroupItemWidget::groupNameChangedSignal, this, &GroupsListWindow::changeGroupName);
    m_groups_list->addItemToList(group_item_widget);
    updateGroupsAmountLabel();
}

void GroupsListWindow::setupButtonsHorLayout()
{
    initCreateNewGroupButton();

    m_buttons_hor_layout->addStretch(1);
    m_buttons_hor_layout->addWidget(m_create_new_group_button.get(), 2);
    m_buttons_hor_layout->addStretch(1);
}

// Slots :

void GroupsListWindow::onEnterGroupButton(size_t id)
{
    emit setToPlayersListWindowSignal(id);
}

void GroupsListWindow::onCreateTeamsButton(size_t id)
{
    emit setToCreateTeamsWindowSignal(id);
}

void GroupsListWindow::onRemoveGroupButton(size_t id)
{
    m_groups_collection->deleteItem(id);
    auto item_to_remove = m_groups_list->m_list->takeItem(id);
    delete item_to_remove;
    for (size_t index = id; index < m_groups_collection->getSize(); index++)
    {
        m_groups_collection->getItem(index)->setId(static_cast<uint16_t>(index));
    }
    m_groups_list->removeAllItemsFromList();
    initList();
}

void GroupsListWindow::onCreateNewGroupButton()
{
    GroupInputDialog group_input_dialog(this);
    if (group_input_dialog.exec() == QDialog::Accepted)
    {
        QString group_name      = group_input_dialog.getGroupName();
        int     teams           = group_input_dialog.getTeamsAmount();
        int     players_in_team = group_input_dialog.getPlayersInTeamAmount();

        Group::Config group_config;
        group_config.id                     = static_cast<uint16_t>(m_groups_collection->getSize());
        group_config.name                   = group_name.toStdString();
        group_config.teams_amount           = static_cast<uint16_t>(teams);
        group_config.players_in_team_amount = static_cast<uint16_t>(players_in_team);

        std::shared_ptr<Group> newGroup = std::make_shared<Group>(group_config);
        m_groups_collection->addItem(newGroup);
        addGroupItemToList(newGroup);
    }
}