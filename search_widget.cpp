#include "search_widget.hpp"

SearchWidget::SearchWidget(QStringList *possibilities) 
{
    if (possibilities)
    {
        m_possibilities = possibilities;
        QVBoxLayout *layout = new QVBoxLayout(this);

        searchLineEdit = new QLineEdit(this);
        connect(searchLineEdit, &QLineEdit::textChanged, this, &SearchWidget::onSearchTextChanged);

        suggestionsListView = new QListView(this);
        suggestionsModel = new QStandardItemModel(this);
        suggestionsListView->setModel(suggestionsModel);
        for (const QString &possibility : *m_possibilities)
        {
            QStandardItem *item = new QStandardItem(possibility);
            suggestionsModel->appendRow(item);
        }

        layout->addWidget(searchLineEdit);
        layout->addWidget(suggestionsListView);
    }
}

void SearchWidget::onSearchTextChanged()
{
    QString search_text = searchLineEdit->text();
    
    // Emit the signal to notify the main window about the search text change
    emit searchTextChanged(search_text);

    // Clear the suggestions model
    suggestionsModel->clear();

    for (const QString &possibility : *m_possibilities)
    {
        if (possibility.startsWith(search_text, Qt::CaseInsensitive))
        {
            QStandardItem *item = new QStandardItem(possibility);
            suggestionsModel->appendRow(item);
        }
    }
}
