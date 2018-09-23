#include "CategoryEntryModel.hpp"

#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

namespace kodew
{

CategoryEntryModel::CategoryEntryModel(QObject *parent)
    : QAbstractListModel(parent)
{
  auto query = QSqlQuery();
  query.setForwardOnly(true);
  query.exec("SELECT distinct category FROM TSnippets");
  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
    return;
  }

  while(query.next()) {
    m_data.push_back(query.value(0).toString());
  }
}

int CategoryEntryModel::rowCount(const QModelIndex &parent) const
{
  return m_data.count();
}

QVariant CategoryEntryModel::data(const QModelIndex &index, int role) const
{
  int row = index.row();

  if(row < 0 || row >= m_data.count()) {
      return QVariant();
  }

  switch (role)
  {
  case Qt::DisplayRole:
    return m_data.value(row);
  }

  return QVariant();
}


void CategoryEntryModel::refresh()
{
  auto query = QSqlQuery();
  query.setForwardOnly(true);
  query.exec("SELECT distinct category FROM TSnippets");
  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
    return;
  }

  beginResetModel();
  m_data.clear();
  while(query.next()) {
    m_data.push_back(query.value(0).toString());
  }
  endResetModel();
}

} // namespace kodew
