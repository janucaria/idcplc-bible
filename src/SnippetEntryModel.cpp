#include "SnippetEntryModel.hpp"

#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

namespace kodew
{

SnippetEntryModel::SnippetEntryModel(QObject *parent)
    : QAbstractListModel(parent)
{
  m_roleNames[static_cast<int>(RoleNames::IdRole)] = "xid";
  m_roleNames[static_cast<int>(RoleNames::TitleRole)] = "title";

  auto query = QSqlQuery();
  query.setForwardOnly(true);
  query.exec("SELECT xid, title FROM TSnippets");

  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
    return;
  }

  m_data.clear();
  while(query.next()) {
    m_data.push_back({
      query.value(0).toInt(),
      query.value(1).toString()
    });
  }
}

int SnippetEntryModel::rowCount(const QModelIndex &parent) const
{
  return m_data.count();
}

QVariant SnippetEntryModel::data(const QModelIndex &index, int role) const
{
  int row = index.row();

  if(row < 0 || row >= m_data.count()) {
      return QVariant();
  }

  switch (static_cast<RoleNames>(role))
  {
  case RoleNames::IdRole:
    return m_data.value(row).xid;
  case RoleNames::TitleRole:
    return m_data.value(row).title;
  }

  return QVariant();
}

QHash<int, QByteArray> SnippetEntryModel::roleNames() const
{
  return m_roleNames;
}

void SnippetEntryModel::setCategory(const QString& cat)
{
  m_category = cat;

  auto query = QSqlQuery();
  query.setForwardOnly(true);
  query.prepare("SELECT xid, title FROM TSnippets WHERE category=?");
  query.bindValue(0, m_category);
  query.exec();

  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
    return;
  }

  beginResetModel();
  m_data.clear();
  while(query.next()) {
    m_data.push_back({
      query.value(0).toInt(),
      query.value(1).toString()
    });
  }
  endResetModel();
}

QString SnippetEntryModel::category() {
  return m_category;
}

void SnippetEntryModel::refresh()
{
  auto query = QSqlQuery();
  query.setForwardOnly(true);
  query.exec("SELECT xid, title FROM TSnippets");

  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
    return;
  }

  beginResetModel();
  m_data.clear();
  while(query.next()) {
    m_data.push_back({
      query.value(0).toInt(),
      query.value(1).toString()
    });
  }
  endResetModel();
}

} // namespace kodew
