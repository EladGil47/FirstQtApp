#ifndef FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H
#define FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H

#include "group.hpp"
#include "editable_label.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class GroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    GroupItemWidget(std::shared_ptr<Group> group= nullptr);

private:

size_t m_group_index ; 
void mouseDoubleClickEvent(QMouseEvent *event) override;



void initNameLabel();
void initSizeLabel();
void adjustButtonsSize();
void initButtons();
void initEnterButton();
void initCreateTeamsButton();
void initRemoveButton();
void setupLayout();

std::shared_ptr<Group> m_group;

EditableLabel* m_name_label;
QLabel* m_size_label;
QPushButton* m_enter_button;
QPushButton* m_create_teams_button;
QPushButton* m_remove_button;








public slots:
void onEnterButtonClicked();
void onCreateTeamsButtonClicked();
void onRemoveButtonClicked();
void onChangeGroupName(const QString& name);

signals:
    void enterButtonClickedSignal(size_t id);
    void createTeamsButtonClickedSignal(size_t id);
    void removeButtonClickedSignal(size_t id);
    void groupNameChangedSignal(size_t id,std::string name);

};
#endif // FIRST_QT_APP_INCLUDE_GROUP_ITEM_WIDGET_H