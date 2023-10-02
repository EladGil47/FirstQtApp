#ifndef FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H

#include "base_player_item_widget.hpp"

#include <QCheckBox>
#include <QMouseEvent>

class CheckablePlayerItemWidget : public BasePlayerItemWidget
{
    Q_OBJECT

public:
    CheckablePlayerItemWidget(std::shared_ptr<Player> player)
        : BasePlayerItemWidget(player)
    {

        m_name_label->setEditablity(false);
        initIsSelectedCheckBox();

        setupLayout();
    }

  

    void setIsCheckBoxEnabled(bool state)
    {
        m_is_click_enabled = state;
        m_is_selected_check_box->setEnabled(state);
    }

    Qt::CheckState getCheckBoxState()
    {
        return m_is_selected_check_box->checkState();
    }

private:
    QCheckBox *m_is_selected_check_box;
    bool m_is_click_enabled = true;

    void setupLayout()
    {
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(m_is_selected_check_box);
        layout->addWidget(m_name_label);
        layout->addWidget(m_rate_label);
        QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
        layout->addSpacerItem(spacer);
    }

    void mousePressEvent(QMouseEvent *event)
    {
        if (m_is_click_enabled && event->button() == Qt::LeftButton)
        {
            m_is_selected_check_box->setChecked(!m_is_selected_check_box->isChecked());
        }

        QWidget::mousePressEvent(event);
    }

    void initIsSelectedCheckBox()
    {
        m_is_selected_check_box = new QCheckBox;
        m_is_selected_check_box->setStyleSheet(
            "QCheckBox::indicator {"
            "    border: 1px solid black;"
            "    background-color: white;"
            "    width: 24px; /* Increase the checkbox width */"
            "    height: 24px; /* Increase the checkbox height */"
            "}"
            "QCheckBox::indicator::checked {"
            "   background-color : rgba(0,60,255,60%);"
            "}");
        connect(m_is_selected_check_box, &QCheckBox::stateChanged, this, onCheckBoxStateChanged);
    }

private slots:

    void onCheckBoxStateChanged(int state)
    {
        emit checkBoxStateChangedSignal(m_player_index, state);
    }

signals:
    void checkBoxStateChangedSignal(size_t id, int state);
};
#endif // FIRST_QT_APP_INCLUDE_CHECKABLE_ITEM_WIDGET_H
