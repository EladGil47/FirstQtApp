
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
    m_name_label = new EditableLabel(this);
    m_name_label->setText(name);
    m_name_label->setAlignment(Qt::AlignLeft);
    m_name_label->setFont(QFont(Common::FONT_FAMILY_NAME, 14, QFont::Bold));
    m_name_label->setMaxLength(MaxValues::ITEM_WIDGET_LABEL_NAME);
    connect(m_name_label,EditableLabel::finishEditingSig, this, onChangeGroupName);
}



void GroupItemWidget::setSizeLabel()
{
    QString size = QString::number(m_group->getNumOfPlayers());
    QString size_wrapped = "(" + size + ")";
    m_size_label = new QLabel(size_wrapped, this);
    m_size_label->setFont(QFont(Common::FONT_FAMILY_NAME, 14, QFont::Bold));
}

void GroupItemWidget::setEnterButton()
{
    m_enter_button = new QPushButton("Enter ");
    m_enter_button->setFixedSize(Sizes::WIDGET_IN_GROUP_ITEM_WIDGET);
    m_enter_button->setStyleSheet(
   "QPushButton {"
    "    background-color: #0074CC;"    /* Blue background color */
    "    border: 2px solid #0074CC;"    /* Blue border */
    "    color: white;"                  /* White text color */
    "    padding: 3px 20px;"             /* Reduced vertical padding, same horizontal padding */
    "    font-size: 18px;"               /* Font size */
    "    font-weight: bold;"             /* Bold text */
    "}"
    "QPushButton:hover {"
    "    background-color: #005FAA;"    /* Darker blue on hover */
    "    border: 2px solid #005FAA;"    /* Darker blue border on hover */
    "}"
                                  );
    connect(m_enter_button, &QPushButton::clicked, this,onEnterButtonClicked);
}

void GroupItemWidget::setRemoveButton()
{
    m_remove_button = new QPushButton("Remove");
    m_remove_button->setFixedSize(Sizes::WIDGET_IN_GROUP_ITEM_WIDGET);
    m_remove_button->setStyleSheet(
        "QPushButton {"
    "    background-color: #FF0000;"   /* Red background color */
    "    border: 2px solid #FF0000;"   /* Red border */
    "    color: white;"                /* White text color */
    "    padding: 3px 20px;"          /* Padding around the text */
    "    font-size: 18px;"             /* Font size */
    "    font-weight: bold;"           /* Bold text */
    "}"

    "QPushButton:hover {"
    "    background-color: #FF3333;"   /* Darker red on hover */
    "    border: 2px solid #FF3333;"   /* Darker red border on hover */
    "}"
    );
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


