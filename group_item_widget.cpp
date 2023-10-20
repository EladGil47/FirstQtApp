#include "group_item_widget.h"
#include "app_common.hpp"

#include <QMouseEvent>
#include <QMessageBox>


GroupItemWidget::GroupItemWidget(std::shared_ptr<Group> group)
{
    if (group)
    {
        m_group = group ;
        m_group_index = static_cast<size_t>(m_group->getId());

        initNameLabel();
        initSizeLabel();
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
    QString name = QString::fromStdString(m_group->getName());
    m_name_label = new EditableLabel;
    m_name_label->setMaxLength(MaxValues::ITEM_WIDGET_LABEL_NAME);
    m_name_label->setText(name);
    m_name_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);
    connect(m_name_label,&EditableLabel::finishEditingSig, this, &GroupItemWidget::onChangeGroupName);
}

void GroupItemWidget::initSizeLabel()
{
    QString size = QString::number(m_group->getNumOfPlayers());
    QString size_wrapped = "(" + size + ")";
    m_size_label = new QLabel(size_wrapped);
    m_size_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);

}

void GroupItemWidget::initEnterButton()
{
    m_enter_button = new QPushButton("Enter");
    m_enter_button->setStyleSheet(Style::BLUE_BUTTON_HOR_LAYOUT);
    connect(m_enter_button, &QPushButton::clicked, this,&GroupItemWidget::onEnterButtonClicked);
}

void GroupItemWidget::initCreateTeamsButton()
{
    m_create_teams_button = new QPushButton("Create Teams");
    m_create_teams_button->setStyleSheet(Style::GREEN_BUTTON_HOR_LAYOUT);
    connect(m_create_teams_button, &QPushButton::clicked, this,&GroupItemWidget::onCreateTeamsButtonClicked);
}

void GroupItemWidget::initRemoveButton()
{
    m_remove_button = new QPushButton("Remove");
    m_remove_button->setStyleSheet(Style::RED_BUTTON_HOR_LAYOUT);
    connect(m_remove_button, &QPushButton::clicked, this,&GroupItemWidget::onRemoveButtonClicked);
}

void GroupItemWidget::adjustButtonsSize()
{
    QList<QPushButton*> buttons = { m_enter_button, m_create_teams_button, m_remove_button };

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
    if (m_name_label && m_size_label && m_enter_button && m_create_teams_button && m_remove_button)
    {
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(m_name_label);
        layout->addWidget(m_size_label);
        QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addSpacerItem(spacer);
        layout->addWidget(m_enter_button);
        layout->addWidget(m_create_teams_button);
        layout->addWidget(m_remove_button);
    }
    else{
        qFatal("Error: Failed to set GroupItemWidget.\nOne or more required pointers are not set.");
    }
}

void GroupItemWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit enterButtonClickedSignal(m_group_index);
    }
}

void GroupItemWidget::initAddMorePlayersMessageBox()
{
    QMessageBox message_box;
    message_box.setWindowTitle("Warning");
    message_box.setIcon(QMessageBox::Warning);
    message_box.setStyleSheet(Settings::MESSAGES_BOX_COLOR);
    message_box.setFont(Fonts::PLAYER_ITEM_WIDGET_FONT);
    message_box.setText("Please add more players to create teams");
    message_box.setStandardButtons(QMessageBox::Ok);
    message_box.exec();
}

// Slots : 

void GroupItemWidget::onEnterButtonClicked()
{
    emit enterButtonClickedSignal(m_group_index);
}

void GroupItemWidget::onCreateTeamsButtonClicked()
{
    uint16_t minimun_required_players_amount = m_group->getPlayersInTeamAmount() * m_group->getTeamsAmount();
    if (m_group->getNumOfPlayers() >= static_cast<size_t>(minimun_required_players_amount))
    {
        emit createTeamsButtonClickedSignal(m_group_index);
    }
    else{
        initAddMorePlayersMessageBox();
    }
}

void GroupItemWidget::onRemoveButtonClicked()
{
    emit removeButtonClickedSignal(m_group_index);
}

void GroupItemWidget::onChangeGroupName(const QString& name)
{
    emit groupNameChangedSignal(m_group_index,name.toStdString());
}
