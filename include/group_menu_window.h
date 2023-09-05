#include <QMainWindow>
#include <QWidget>

class GroupMenuWindow : public QMainWindow {
    Q_OBJECT

public:
    GroupMenuWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        // Set window properties
        setWindowTitle("My New Window");
        resize(400, 300); // Set the initial size of the window

        // Create a central widget to hold the contents of the window
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
    }
};