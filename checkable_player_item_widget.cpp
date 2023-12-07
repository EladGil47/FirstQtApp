// checkable_item_widget.cpp
#include "checkable_player_item_widget.hpp"

CheckablePlayerItemWidget::CheckablePlayerItemWidget(std::shared_ptr<Player> player)
    : BasePlayerItemWidget(player)
{
    initNameLabel(QString::fromStdString(player->getName()));
    initIsSelectedCheckBox();

    setupLayout();
}

void CheckablePlayerItemWidget::setIsCheckBoxEnabled(bool state)
{
    m_is_click_enabled = state;
    m_is_selected_check_box->setEnabled(state);
}

void CheckablePlayerItemWidget::setCheckState(Qt::CheckState state)
{
    m_is_selected_check_box->setCheckState(state);
}

Qt::CheckState CheckablePlayerItemWidget::getCheckBoxState()
{
    return m_is_selected_check_box->checkState();
}

void CheckablePlayerItemWidget::setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_is_selected_check_box);
    layout->addWidget(m_name_label);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addSpacerItem(spacer);
    layout->setContentsMargins(10, 0, 0, 0);
}

void CheckablePlayerItemWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_is_click_enabled && event->button() == Qt::LeftButton)
    {
        m_is_selected_check_box->setChecked(!m_is_selected_check_box->isChecked());
    }

    QWidget::mousePressEvent(event);
}

void CheckablePlayerItemWidget::initIsSelectedCheckBox()
{
    m_is_selected_check_box = new QCheckBox;
    m_is_selected_check_box->setStyleSheet(
        "QCheckBox::indicator {"
        "    border: white;"
        "    border-radius: 6px;" // Make it circular
        "    background-color: white;"
        "    width: 12px;"
        "    height: 12px;"
        "}"
        "QCheckBox::indicator:checked {"
        "   background-color: #4CAF50;" // Green color when checked
        "}");
    connect(m_is_selected_check_box, &QCheckBox::stateChanged, this, &CheckablePlayerItemWidget::onCheckBoxStateChanged);
}

void CheckablePlayerItemWidget::onCheckBoxStateChanged(int state)
{
    emit checkBoxStateChangedSignal(m_player_index, state);
}
