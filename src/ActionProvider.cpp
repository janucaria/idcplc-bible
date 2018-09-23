#include "ActionProvider.hpp"
#include <QDebug>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QSqlQuery>
#include <QSqlError>

namespace kodew
{

ActionProvider &
ActionProvider::instance()
{
  static ActionProvider self;
  return self;
}

void ActionProvider::displaySnippetById(QObject *codeViewer, int id)
{
  auto query = QSqlQuery();
  query.setForwardOnly(true);
  query.prepare("SELECT title, description, snippet FROM TSnippets WHERE xid=?");
  query.bindValue(0, id);
  query.exec();

  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
    return;
  }

  query.first();
  qvariant_cast<QObject *>(codeViewer->property("labelTitle"))->setProperty("text", query.value("title").toString());
  qvariant_cast<QObject *>(codeViewer->property("labelDescription"))->setProperty("text", query.value("description").toString());
  qvariant_cast<QObject *>(codeViewer->property("sourceView"))->setProperty("text", query.value("snippet").toString());
}

void ActionProvider::editSnippetForm(QObject *snippetForm, int idSnippet)
{
  auto query = QSqlQuery();
  query.setForwardOnly(true);
  query.prepare("SELECT contributor, title, category, languages, description, snippet FROM TSnippets WHERE xid=?");
  query.bindValue(0, idSnippet);
  query.exec();

  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
    return;
  }

  query.first();
  snippetForm->setProperty("idValue", idSnippet);
  snippetForm->setProperty("contributorText", query.value("contributor").toString());
  snippetForm->setProperty("titleText", query.value("title").toString());
  snippetForm->setProperty("categoryText", query.value("category").toString());
  snippetForm->setProperty("descriptionText", query.value("description").toString());
  snippetForm->setProperty("snippetText", query.value("snippet").toString());
  snippetForm->setProperty("visible", true);
}

void ActionProvider::saveSnippet(QObject* addSnippetView)
{
  addSnippetView->setProperty("visible", false);

  auto query = QSqlQuery();
  query.setForwardOnly(true);

  auto idValue = addSnippetView->property("idValue").toInt(); 
  auto contributor = addSnippetView->property("contributorText").toString();
  auto title = addSnippetView->property("titleText").toString();
  auto category = addSnippetView->property("categoryText").toString();
  auto languages = addSnippetView->property("languagesText").toString();
  auto description = addSnippetView->property("descriptionText").toString();
  auto snippet = addSnippetView->property("snippetText").toString();

  if(idValue) {
    query.prepare(R"(
      UPDATE TSnippets
      SET contributor = ?,
          title = ?,
          category = ?,
          languages = ?,
          description = ?,
          snippet = ?
      WHERE
          xid = ?
    )");
    query.addBindValue(contributor);
    query.addBindValue(title);
    query.addBindValue(category);
    query.addBindValue(languages);
    query.addBindValue(description);
    query.addBindValue(snippet);
    query.addBindValue(idValue);
  } else {
    query.prepare(R"(
      INSERT INTO TSnippets
        (contributor, title, category, languages, description, snippet)
      VALUES
        (?, ?, ?, ?, ?, ?)
    )");
    query.addBindValue(contributor);
    query.addBindValue(title);
    query.addBindValue(category);
    query.addBindValue(languages);
    query.addBindValue(description);
    query.addBindValue(snippet);
  }

  query.exec();

  if (!query.isActive())
  {
    qWarning() << "ERROR: " << query.lastError().text();
  }
}

} // namespace kodew