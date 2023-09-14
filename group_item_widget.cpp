
#include "group_item_widget.h"

GroupItemWidget::GroupItemWidget(std::shared_ptr<Group> group, MainWindow *parent)
    :  m_group(group) , m_main_window(parent)
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
    m_name_label->getLabel()->setText(name);
    m_name_label->getLabel()->setAlignment(Qt::AlignLeft);
    // TODO connecit to slot that transfer the new namd and the index of this item
    // connect(m_name_label,EditableLabel::finishEditingSig, m_main_window, MainWindow::updateList);
}

void GroupItemWidget::setSizeLabel()
{
    QString size = QString::number(m_group->getNumOfPlayers());
    QString size_wrapped = "(" + size + ")";
    m_size_label = new QLabel(size_wrapped, this);
    m_size_label->setStyleSheet(
        "QLabel {"
        "    color: black;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}");
}

void GroupItemWidget::setEnterButton()
{
    m_enter_button = new QPushButton("Enter");
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
    m_item_hor_layout->addWidget(m_name_label, 2);
    m_item_hor_layout->addWidget(m_size_label, 4);
    m_item_hor_layout->addWidget(m_enter_button, 1);
    m_item_hor_layout->addWidget(m_remove_button, 1);
}

// Slots : 

void GroupItemWidget::onEnterButtonClicked(bool a)
{
 m_main_window->onEnterGroupButton(m_group_index);
}
void GroupItemWidget::onRemoveButtonClicked(bool a)
{
 m_main_window->onRemoveGroupButton(m_group_index);
}


