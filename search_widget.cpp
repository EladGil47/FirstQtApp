#include "search_widget.hpp"

#include <QDialogButtonBox>

SearchWidget::SearchWidget(QStringList *possibilities) 
{
    if (possibilities)
    {
        m_possibilities = possibilities;
        QVBoxLayout *layout = new QVBoxLayout(this);

        m_search_line_edit = new QLineEdit(this);
        connect(m_search_line_edit, &QLineEdit::textChanged, this, &SearchWidget::onSearchTextChanged);

        suggestionsListView = new QListView(this);
        suggestionsModel = new QStandardItemModel(this);
        suggestionsListView->setModel(suggestionsModel);
        for (const QString &possibility : *m_possibilities)
        {
            QStandardItem *item = new QStandardItem(possibility);
            suggestionsModel->appendRow(item);
        }

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &SearchWidget::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &SearchWidget::reject);


        connect(suggestionsListView, &QListView::clicked, this, &SearchWidget::onItemClicked);
        connect(suggestionsListView, &QListView::doubleClicked, this, &SearchWidget::onItemDoubleClicked);

        layout->addWidget(m_search_line_edit);
        layout->addWidget(suggestionsListView);
        layout->addWidget(buttonBox);

    }
}

void SearchWidget::onItemClicked(const QModelIndex &index)
{
    QString selected_item = index.data(Qt::DisplayRole).toString();
    emit itemSelected(selected_item);
    m_search_line_edit->setText(selected_item);
}

void SearchWidget::onItemDoubleClicked(const QModelIndex &index)
{
    QString selected_item = index.data(Qt::DisplayRole).toString();
    emit itemSelected(selected_item);
    m_search_line_edit->setText(selected_item);
}

void SearchWidget::onSearchTextChanged()
{
    QString search_text = m_search_line_edit->text();
    
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

QString SearchWidget::getSearchText() const
{
    return m_search_line_edit->text();
}