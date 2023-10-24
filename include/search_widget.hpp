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
    QString getSearchText() const;

signals:
    void searchTextChanged(const QString &text);
    void itemSelected(const QString &selectedItem);

private slots:
    void onSearchTextChanged();
    void onItemClicked(const QModelIndex &index);
    void onItemDoubleClicked(const QModelIndex &index);

private:
    QLineEdit *m_search_line_edit;
    QListView *suggestionsListView;
    QStandardItemModel *suggestionsModel;
    QStringList * m_possibilities;
};
#endif // FIRST_QT_APP_INCLUDE_SEARCH_WIDGET_H

