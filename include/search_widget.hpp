#ifndef FIRST_QT_APP_INCLUDE_SEARCH_WIDGET_H
#define FIRST_QT_APP_INCLUDE_SEARCH_WIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QListView>
#include <QStandardItemModel>

class SearchWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SearchWidget(QStringList *possibilities);

signals:
    void searchTextChanged(const QString &text);

private slots:
    void onSearchTextChanged();

private:
    QLineEdit *searchLineEdit;
    QListView *suggestionsListView;
    QStandardItemModel *suggestionsModel;
    QStringList * m_possibilities;
};
#endif // FIRST_QT_APP_INCLUDE_SEARCH_WIDGET_H

