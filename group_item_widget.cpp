#include "group_item_widget.h"
#include "app_common.hpp"

GroupItemWidget::GroupItemWidget(std::shared_ptr<Group> group)
    :  m_group(group) 
{
    if (group != nullptr)
    {
        setGroupIndex(static_cast<size_t>(m_group->getId()));
        setNameLabel();
        setSizeLabel();
        setEnterButton();
        setRemoveButton();
        setItemHorLayout();
    }
}

void GroupItemWidget::setGroupIndex(size_t group_index)
{
    m_group_index = group_index;
}

void GroupItemWidget::setNameLabel()
{
    QString name = QString::fromStdString(m_group->getName());
    m_name_label = new EditableLabel;
    m_name_label->setText(name);
    m_name_label->setAlignment(Qt::AlignLeft);
    m_name_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);
    m_name_label->setMaxLength(MaxValues::ITEM_WIDGET_LABEL_NAME);
    connect(m_name_label,SIGNAL(EditableLabel::finishEditingSig(const QString&))finishEditingSig, this, SLOT(onChangeGroupName(const QString&)));
}

void GroupItemWidget::setSizeLabel()
{
    QString size = QString::number(m_group->getNumOfPlayers());
    QString size_wrapped = "(" + size + ")";
    m_size_label = new QLabel(size_wrapped);
    m_size_label->setFont(Fonts::GROUP_ITEM_WIDGET_FONT);
}

void GroupItemWidget::setEnterButton()
{
    m_enter_button = new QPushButton("Enter ");
    m_enter_button->setFixedSize(Sizes::WIDGET_IN_GROUP_ITEM_WIDGET);
    m_enter_button->setStyleSheet(Style::BLUE_BUTTON_HOR_LAYOUT);
    connect(m_enter_button, &QPushButton::clicked, this,onEnterButtonClicked);
}

void GroupItemWidget::setRemoveButton()
{
    m_remove_button = new QPushButton("Remove");
    m_remove_button->setFixedSize(Sizes::WIDGET_IN_GROUP_ITEM_WIDGET);
    m_remove_button->setStyleSheet(Style::RED_BUTTON_HOR_LAYOUT);
    connect(m_remove_button, &QPushButton::clicked, this,onRemoveButtonClicked);
}

void GroupItemWidget::setItemHorLayout()
{
    m_item_hor_layout = new QHBoxLayout(this);
    m_item_hor_layout->addWidget(m_name_label);
    m_item_hor_layout->addWidget(m_size_label);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_item_hor_layout->addSpacerItem(spacer);
    m_item_hor_layout->addWidget(m_enter_button);
    m_item_hor_layout->addWidget(m_remove_button);
}

// Slots : 

void GroupItemWidget::onEnterButtonClicked()
{
    emit enterButtonClickedSignal(m_group_index);
}
void GroupItemWidget::onRemoveButtonClicked()
{
    emit removeButtonClickedSignal(m_group_index);
}

void GroupItemWidget::onChangeGroupName(const QString& name)
{
    emit groupNameChangedSignal(m_group_index,name.toStdString());
}