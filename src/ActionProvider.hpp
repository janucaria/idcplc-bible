#ifndef KODEW_ACTION_PROVIDER_HPP
#define KODEW_ACTION_PROVIDER_HPP

#include <QObject>
#include <QString>

namespace kodew {
  class ActionProvider : public ::QObject {
    Q_OBJECT

    public:
    static ActionProvider& instance();

    Q_INVOKABLE void displaySnippetById(QObject* codeViewer, int id);
    
    Q_INVOKABLE void editSnippetForm(QObject* snippetForm, int idSnippet);

    Q_INVOKABLE void saveSnippet(QObject* addSnippetView);

    private:

    ActionProvider() = default;
  };
}

#endif