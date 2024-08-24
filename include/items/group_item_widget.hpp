#ifndef FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H

#include "editable_label.hpp"
#include "group.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include <memory>

class GroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    GroupItemWidget(std::shared_ptr<Group> group = nullptr);

private:
    size_t m_group_index;
    void   mouseDoubleClickEvent(QMouseEvent* event) override;

    void initNameLabel();
    void initSizeLabel();
    void initInfoLabel();

    void adjustButtonsSize();
    void initButtons();
    void initEnterButton();
    void initCreateTeamsButton();
    void initRemoveButton();
    void setupLayout();

    std::shared_ptr<Group> m_group;

    std::unique_ptr<EditableLabel> m_name_label;
    std::unique_ptr<QLabel>        m_size_label;
    std::unique_ptr<QLabel>        m_info_label;
    std::unique_ptr<QPushButton>   m_enter_button;
    std::unique_ptr<QPushButton>   m_create_teams_button;
    std::unique_ptr<QPushButton>   m_remove_button;

public slots:
    void onEnterButtonClicked();
    void onCreateTeamsButtonClicked();
    void onRemoveButtonClicked();
    void onChangeGroupName(const QString& name);

signals:
    void enterButtonClickedSignal(size_t id);
    void createTeamsButtonClickedSignal(size_t id);
    void removeButtonClickedSignal(size_t id);
    void groupNameChangedSignal(size_t id, std::string name);
};
#endif // FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H