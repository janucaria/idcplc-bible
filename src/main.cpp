#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QQuickTextDocument>
#include <QObject>
#include <QIcon>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include "highlighter.h"
#include "dragdrophandler.h" // dragdrop file handler

#include "ActionProvider.hpp"
#include "CategoryEntryModel.hpp"
#include "SnippetEntryModel.hpp"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("qrc:/res/idcplc.ico"));

    QFontDatabase::addApplicationFont("qrc:/res/Consolas.ttf");

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if (!db.open())
    {
        qWarning() << "ERROR: " << db.lastError();
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

    {
        QSqlQuery query("CREATE TABLE IF NOT EXISTS TSnippets (xid INTEGER PRIMARY KEY, contributor text, title text, description text, snippet text, platforms text, languages text, dialects text, category text, tag text, src text, checksum text, updated integer)");

        if (!query.isActive())
        {
            qWarning() << "ERROR: " << query.lastError().text();
        }
    }
    {
        QSqlQuery query("CREATE INDEX IF NOT EXISTS TSnippetsContributorIndex ON TSnippets (contributor)");
        if (!query.isActive())
        {
            qWarning() << "ERROR: " << query.lastError().text();
        }
    }

    qmlRegisterType<kodew::CategoryEntryModel>("idcplc.kodew", 0, 1, "CategoryEntryModel");
    qmlRegisterType<kodew::SnippetEntryModel>("idcplc.kodew", 0, 1, "SnippetEntryModel");

    qmlRegisterSingletonType<kodew::ActionProvider>("ActionProvider", 0, 1, "ActionProvider",
                                                    [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
                                                        QQmlEngine::setObjectOwnership(&kodew::ActionProvider::instance(), QQmlEngine::CppOwnership);
                                                        return &kodew::ActionProvider::instance();
                                                    });

    QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml"));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    // Cari sourceView object di qml hirarki untuk dipasangkan highlighter.
    Highlighter *highlighter;
    QObject *root = engine.rootObjects()[0];
    QObject *sourceView = root->findChild<QObject *>("sourceView");
    if (sourceView != NULL)
    {
        QQuickTextDocument *doc = qvariant_cast<QQuickTextDocument *>(sourceView->property("textDocument"));
        if (doc != NULL)
        {
            highlighter = new Highlighter(doc->textDocument());

            // Override tab width menjadi 30 device unit.
            QTextOption textOptions = doc->textDocument()->defaultTextOption();
            textOptions.setTabStop(30);
            doc->textDocument()->setDefaultTextOption(textOptions);
        }
    }

    // untuk dragdrop file
    DragDropHandler ddh(root);
    QObject *dropArea = sourceView->findChild<QObject *>("dropArea");
    QObject::connect(dropArea, SIGNAL(dropSignal(QString)),
                     &ddh, SLOT(runHandler(QString)));

    return app.exec();
}
