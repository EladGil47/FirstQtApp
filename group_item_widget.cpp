
#include "group_item_widget.h"

GroupItemWidget::GroupItemWidget(std::shared_ptr<Group> group, MainWindow *parent)
    :  m_group(group) , m_main_window(parent)
{
    if (group != nullptr)
    {
        setNameLabel();
        setSizeLabel();
        setEnterButton();
        setRemoveButton();
        setItemHorLayout();
    }

}

void GroupItemWidget::setNameLabel()
{
    QString name = QString::fromStdString(m_group->getName());
    m_name_label = new QLabel(name, this);
    m_name_label->setFont(QFont("Arial", 16, QFont::Bold));
    m_name_label->setStyleSheet("border: none;");
    m_name_label->setAlignment(Qt::AlignLeft);
}

void GroupItemWidget::setSizeLabel()
{
    QString size = QString::number(m_group->getNumOfPlayers());
    QString size_wrapped = "(" + size + ")";
    m_size_label = new QLabel(size_wrapped, this);
    m_size_label->setFont(QFont("Arial", 16, QFont::Bold));
    m_size_label->setStyleSheet("border: none;");
    m_size_label->setAlignment(Qt::AlignLeft);
}

void GroupItemWidget::setEnterButton()
{
    size_t group_id = m_group->getId();

    m_enter_button = new QPushButton("Enter");
    m_enter_button->setStyleSheet("text-align: center;"
                                  "background-color: green;"
                                  "border: none;");
    connect(m_enter_button, &QPushButton::clicked, m_main_window, [=]()
            { m_main_window->onEnterGroupButton(group_id); });
}
void GroupItemWidget::setRemoveButton()
{
    size_t group_id = m_group->getId();

    m_remove_button = new QPushButton("Remove");
    m_remove_button->setStyleSheet("text-align: center;"
                                   "background-color: red;"
                                   "border: none;");
    connect(m_remove_button, &QPushButton::clicked, m_main_window, [=]()
            { m_main_window->onRemoveGroupButton(group_id); });
}

void GroupItemWidget::setItemHorLayout()
{
    m_item_hor_layout = new QHBoxLayout(this);
    m_item_hor_layout->addWidget(m_name_label, 1);
    m_item_hor_layout->addWidget(m_size_label, 4);
    m_item_hor_layout->addWidget(m_enter_button, 1);
    m_item_hor_layout->addWidget(m_remove_button, 1);
}