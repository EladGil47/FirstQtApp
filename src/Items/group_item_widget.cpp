#include "group_item_widget.hpp"
#include "app_common.hpp"

#include <QMouseEvent>

GroupItemWidget::GroupItemWidget(std::shared_ptr<Group> group)
    : m_group(group),
      m_group_index(static_cast<size_t>(group->getId()))
{
    if (!group)
    {
        qFatal("Error: Group pointer is null.");
    }

    setToolTip("Double-click to enter");

    initNameLabel();
    initSizeLabel();
    initInfoLabel();
    initButtons();
    setupLayout();
}

void GroupItemWidget::initButtons()
{
    // initEnterButton();
    initCreateTeamsButton();
    initRemoveButton();
    adjustButtonsSize();
}

void GroupItemWidget::initNameLabel()
{
    auto name_text = QString::fromStdString(m_group->getName());
    m_name_label   = std::make_unique<EditableLabel>(std::move(createLabel(name_text)));
    connect(m_name_label.get(), &EditableLabel::finishEditingSig, this, &GroupItemWidget::onChangeGroupName);
}

void GroupItemWidget::initSizeLabel()
{
    auto size_text = QString("(%1)").arg(m_group->getNumOfPlayers());
    m_size_label   = createLabel(size_text);
}

void GroupItemWidget::initInfoLabel()
{
    auto info_text = QString("%1 Teams of %2 Players")
                         .arg(m_group->getTeamsAmount())
                         .arg(m_group->getPlayersInTeamAmount());
    m_info_label = createLabel(info_text);
}

std::unique_ptr<QLabel> GroupItemWidget::createLabel(const QString& text)
{
    auto label = std::make_unique<QLabel>(text);
    label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);
    return label;
}

std::unique_ptr<QPushButton> GroupItemWidget::createButton(const QString& text, const QString& style, const QString& tooltip)
{
    auto button = std::make_unique<QPushButton>(text);
    button->setStyleSheet(style);
    button->setToolTip(tooltip);
    return button;
}

// void GroupItemWidget::initEnterButton()
// {
//     m_enter_button = createButton("Enter", Style::BLUE_BUTTON_HOR_LAYOUT, "Click to enter team");
//     connect(m_enter_button.get(), &QPushButton::clicked, this, &GroupItemWidget::onEnterButtonClicked);
// }

void GroupItemWidget::initCreateTeamsButton()
{
    m_create_teams_button = createButton("Create Teams", Style::DARK_BROWN_BUTTON_HOR_LAYOUT, "Click to create Teams");
    connect(m_create_teams_button.get(), &QPushButton::clicked, this, &GroupItemWidget::onCreateTeamsButtonClicked);
}

void GroupItemWidget::initRemoveButton()
{
    m_remove_button = createButton("Remove", Style::DARK_BROWN_BUTTON_HOR_LAYOUT, "Click to remove team");
    connect(m_remove_button.get(), &QPushButton::clicked, this, &GroupItemWidget::onRemoveButtonClicked);
}

void GroupItemWidget::adjustButtonsSize()
{
    const QList<QPushButton*> buttons = {
        // m_enter_button.get(),
        m_create_teams_button.get(),
        m_remove_button.get()};

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
    if (!m_name_label || !m_size_label || !m_info_label || !m_create_teams_button || !m_remove_button)
    {
        qFatal("Error: Failed to set GroupItemWidget. One or more required pointers are not set.");
    }
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_name_label->setFixedWidth(200);
    m_size_label->setFixedWidth(100);
    m_info_label->setFixedWidth(400);

    layout->addWidget(m_name_label.get());
    layout->addWidget(m_size_label.get());
    layout->addWidget(m_info_label.get());
    layout->addStretch();
    layout->addWidget(m_create_teams_button.get());
    layout->addWidget(m_remove_button.get());
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
