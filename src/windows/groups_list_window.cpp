#include "groups_list_window.hpp"

#include <QPixmap>
#include "group_input_dialog.hpp"
#include "group_item_widget.hpp"
#include "resource_paths.hpp"

#include "app_common.hpp"

GroupsListWindow::GroupsListWindow(std::shared_ptr<GroupsCollection> groups_collection)
{
    if (groups_collection)
    {
        m_groups_collection = groups_collection;

        // initAppNameLabel();
        initAppHorLayout();
        initGroupsList();
        initButtonsHorLayout();

        setupLayout();
    }
}

void GroupsListWindow::setupLayout()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    // layout->addWidget(m_app_name_label);
    layout->addLayout(m_app_name_hor_layout);
    layout->addWidget(m_groups_list);
    layout->addLayout(m_buttons_hor_layout);
}

void GroupsListWindow::initAppHorLayout()
{
    m_app_name_hor_layout = new QHBoxLayout;
    m_app_name_hor_layout->addStretch(1);

    QPixmap pixmap(resources_path::SOCCER_BALL); // Assuming the image is in a resource file
    int     width  = 30;
    int     height = 30;
    pixmap         = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel* left_soccer_ball_label = new QLabel;
    left_soccer_ball_label->setPixmap(pixmap);
    m_app_name_hor_layout->addWidget(left_soccer_ball_label);

    initAppNameLabel();
    m_app_name_hor_layout->addWidget(m_app_name_label);

    QLabel* right_soccer_ball_label = new QLabel;
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
    m_app_name_label = new EditableLabel(label);
    m_app_name_label->setEditability(false);
}

void GroupsListWindow::initGroupsList()
{
    m_groups_list = new LabeledListWidget();
    m_groups_list->setListColor(Style::LIST);
    initGroupsAmountLabel();
    initList();
}

GroupsListWindow::~GroupsListWindow()
{
}

void GroupsListWindow::initGroupsAmountLabelText()
{
    QString size = QString::number(m_groups_collection->getSize());
    m_groups_amount_label->setText(size);
}

void GroupsListWindow::initGroupsAmountLabel()
{
    QLabel* groups_text_label = new QLabel("Groups :");
    m_groups_list->addWidgetAboveList(groups_text_label);

    m_groups_amount_label = new QLabel;
    initGroupsAmountLabelText();
    m_groups_amount_label->setFont(Fonts::LIST_LABEL_FONT);
    m_groups_list->addWidgetAboveList(m_groups_amount_label);

    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_groups_list->addSpacerAboveList(spacer);
}
void GroupsListWindow::setGroupsAmountLabelText()
{
    QString size = QString::number(m_groups_collection->getSize());
    m_groups_amount_label->setText(size);
}

void GroupsListWindow::initCreateNewGroupButton()
{
    QString text              = "Create new group";
    m_create_new_group_button = new QPushButton(text);
    m_create_new_group_button->setStyleSheet(Style::DARK_BROWN_BUTTON_HOR_LAYOUT);
    m_create_new_group_button->setToolTip("Click here to create a new group");
    connect(m_create_new_group_button, &QPushButton::clicked, this, &GroupsListWindow::onCreateNewGroupButton);
}

void GroupsListWindow::initList()
{
    for (std::shared_ptr<Group> group : m_groups_collection->getCollectionRef())
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
}

// Slots :

void GroupsListWindow::onCreateNewGroupButton()
{
    GroupInputDialog group_input_dialog(this);
    group_input_dialog.setStyleSheet(ui_settings::DIALOGS_COLOR);
    if (group_input_dialog.exec() == QDialog::Accepted)
    {
        QString groupName       = group_input_dialog.getGroupName();
        int     teams           = group_input_dialog.getTeamsAmount();
        int     players_in_team = group_input_dialog.getPlayersInTeamAmount();

        Group::Config group_config;
        group_config.id           = static_cast<uint16_t>(m_groups_collection->getSize());
        group_config.name         = groupName.toStdString();
        group_config.teams_amount = static_cast<uint16_t>(teams);
        group_config.players_in_team_amount =
            static_cast<uint16_t>(players_in_team);

        std::shared_ptr<Group> newGroup = std::make_shared<Group>(group_config);
        m_groups_collection->addItem(newGroup);
        addGroupItemToList(newGroup);
        setGroupsAmountLabelText();
    }
}

void GroupsListWindow::onRemoveGroupButton(size_t id)
{
    m_groups_collection->deleteItem(id);
    QListWidgetItem* itemToRemove = m_groups_list->m_list->takeItem(id);
    delete itemToRemove;
    for (size_t index = id; index < m_groups_collection->getSize(); index++)
    {
        m_groups_collection->getItem(index)->setId(static_cast<uint16_t>(index));
    }
    m_groups_list->removeAllItemsFromList();
    initList();
    setGroupsAmountLabelText();
}

void GroupsListWindow::onEnterGroupButton(size_t id)
{
    emit setToPlayersListWindowSignal(id);
}

void GroupsListWindow::onCreateTeamsButton(size_t id)
{
    emit setToCreateTeamsWindowSignal(id);
}

void GroupsListWindow::initButtonsHorLayout()
{
    m_buttons_hor_layout = new QHBoxLayout;
    m_buttons_hor_layout->addStretch(1);

    initCreateNewGroupButton();
    m_buttons_hor_layout->addWidget(m_create_new_group_button, 2);

    m_buttons_hor_layout->addStretch(1);
}