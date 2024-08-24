#include "group_item_widget.hpp"
#include "app_common.hpp"

#include <QMouseEvent>

GroupItemWidget::GroupItemWidget(std::shared_ptr<Group> group)
{
    if (group)
    {
        m_group       = group;
        m_group_index = static_cast<size_t>(m_group->getId());

        setToolTip("Double-click to enter");

        initNameLabel();
        initSizeLabel();
        initInfoLabel();
        initButtons();
        setupLayout();
    }
}

void GroupItemWidget::initButtons()
{
    initEnterButton();
    initCreateTeamsButton();
    initRemoveButton();
    adjustButtonsSize();
}

void GroupItemWidget::initNameLabel()
{
    auto name  = QString::fromStdString(m_group->getName());
    auto label = std::make_unique<QLabel>(name);
    label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);
    m_name_label = std::make_unique<EditableLabel>(std::move(label));
    connect(m_name_label.get(), &EditableLabel::finishEditingSig, this, &GroupItemWidget::onChangeGroupName);
}

void GroupItemWidget::initSizeLabel()
{
    auto size         = QString::number(m_group->getNumOfPlayers());
    auto size_wrapped = "(" + size + ")";
    m_size_label      = std::make_unique<QLabel>(size_wrapped);
    m_size_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);
}

void GroupItemWidget::initInfoLabel()
{
    auto teams           = QString::number(m_group->getTeamsAmount());
    auto players_in_team = QString::number(m_group->getPlayersInTeamAmount());

    auto info_text = teams + " Teams of " + players_in_team + " Players";
    m_info_label   = std::make_unique<QLabel>(info_text);
    m_info_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);
}

void GroupItemWidget::initEnterButton()
{
    m_enter_button = std::make_unique<QPushButton>("Enter");
    m_enter_button->setStyleSheet(Style::BLUE_BUTTON_HOR_LAYOUT);
    connect(m_enter_button.get(), &QPushButton::clicked, this, &GroupItemWidget::onEnterButtonClicked);
}

void GroupItemWidget::initCreateTeamsButton()
{
    m_create_teams_button = std::make_unique<QPushButton>("Create Teams");
    m_create_teams_button->setStyleSheet(Style::DARK_BROWN_BUTTON_HOR_LAYOUT);
    m_create_teams_button->setToolTip("Click to create Teams");

    connect(m_create_teams_button.get(), &QPushButton::clicked, this, &GroupItemWidget::onCreateTeamsButtonClicked);
}

void GroupItemWidget::initRemoveButton()
{
    m_remove_button = std::make_unique<QPushButton>("Remove");
    m_remove_button->setStyleSheet(Style::DARK_BROWN_BUTTON_HOR_LAYOUT);
    m_remove_button->setToolTip("Click to remove team");
    connect(m_remove_button.get(), &QPushButton::clicked, this, &GroupItemWidget::onRemoveButtonClicked);
}

void GroupItemWidget::adjustButtonsSize()
{
    QList<QPushButton*> buttons = {m_enter_button.get(), m_create_teams_button.get(), m_remove_button.get()};

    // Find the maximum width among the buttons
    int max_width = 0;
    for (QPushButton* button : buttons)
    {
        if (button)
            max_width = qMax(max_width, button->sizeHint().width());
    }

    // Set the maximum width to all buttons
    for (QPushButton* button : buttons)
    {
        if (button)
        {
            button->setMinimumWidth(max_width);
        }
    }
}

void GroupItemWidget::setupLayout()
{
    if (m_name_label && m_size_label && m_info_label && m_create_teams_button && m_remove_button)
    {
        m_name_label->setFixedWidth(200);
        m_size_label->setFixedWidth(100);
        m_info_label->setFixedWidth(400);

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->addWidget(m_name_label.get());
        layout->addWidget(m_size_label.get());
        layout->addWidget(m_info_label.get());

        layout->addStretch();

        // layout->addWidget(m_enter_button.get());
        layout->addWidget(m_create_teams_button.get());
        layout->addWidget(m_remove_button.get());
    }
    else
    {
        qFatal("Error: Failed to set GroupItemWidget.\nOne or more required pointers are not set.");
    }
}

void GroupItemWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit enterButtonClickedSignal(m_group_index);
    }
}

// Slots :

void GroupItemWidget::onEnterButtonClicked()
{
    emit enterButtonClickedSignal(m_group_index);
}

void GroupItemWidget::onCreateTeamsButtonClicked()
{
    emit createTeamsButtonClickedSignal(m_group_index);
}

void GroupItemWidget::onRemoveButtonClicked()
{
    emit removeButtonClickedSignal(m_group_index);
}

void GroupItemWidget::onChangeGroupName(const QString& name)
{
    emit groupNameChangedSignal(m_group_index, name.toStdString());
}
