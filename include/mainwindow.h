#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QListWidget>

#include "kohot.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Kohot m_kohot;
    
    QVBoxLayout *createMainLayout();
    void updateGroupListWidget()
    {
         for (int i = 0; i < 50; ++i)
        {
            QPushButton *button = new QPushButton("Button " + QString::number(i + 1));
            // Set text alignment to left
            button->setStyleSheet("text-align: left;");

            QListWidgetItem *item = new QListWidgetItem(m_groupsListWidget);
            m_groupsListWidget->addItem(item);
            m_groupsListWidget->setItemWidget(item, button);
        }

    }

    QVBoxLayout *createGroupsLayout()
    {
        QVBoxLayout *groupsLayout = new QVBoxLayout;

        // Create a QLabel for "Groups:"
        QLabel *groupsLabel = new QLabel("Groups :", this);
        groupsLayout->addWidget(groupsLabel);

        // Create a QListWidget to hold the list of groups
        // QListWidget *m_groupsListWidget = new QListWidget(this);
        groupsLayout->addWidget(m_groupsListWidget);

        // *****************************************
        // ON RUN TIME, I WANT IT FROM OUTSIDE
        // Create and add QPushButton items to the QListWidget
        updateGroupListWidget();
        // *****************************************

        return groupsLayout;
    }

    QHBoxLayout *createButtonSectionLayout()
    {
        QHBoxLayout *buttonSectionLayout = new QHBoxLayout;

        // for(m_kohot)

        // Create 4 horizontal layouts for the buttons
        QPushButton *button1 = createButton("Button 1");
        QPushButton *button2 = createButton("Button 2");
        QPushButton *button3 = createButton("Button 3");
        QPushButton *button4 = createButton("Button 4");

        // Add the button layouts to the vertical layout
        buttonSectionLayout->addWidget(button1,1);
        buttonSectionLayout->addWidget(button2,1);
        buttonSectionLayout->addWidget(button3,1);
        buttonSectionLayout->addWidget(button4,1);

        return buttonSectionLayout;
    }

    QPushButton *createButton(const QString &buttonText)
    {
        QPushButton *button = new QPushButton(buttonText, this);

        // Connect the button's clicked signal to a slot or lambda (optional)
        connect(button, &QPushButton::clicked, [buttonText]() {
            qDebug() << "Button clicked:" << buttonText;
        });

        return button;
    }

private:
    Ui::MainWindow *ui;
    QLabel *createWelcomeLabel();
    QListWidget *m_groupsListWidget = new QListWidget(this);


};
#endif // MAINWINDOW_H
