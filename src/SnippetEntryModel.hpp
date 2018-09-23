#ifndef KODEW_SNIPPET_ENTRY_MODEL_HPP
#define KODEW_SNIPPET_ENTRY_MODEL_HPP

#include <QtCore>

namespace kodew
{

class SnippetEntryModel : public QAbstractListModel
{
    Q_OBJECT
  public:
    struct SnippetData {
      int xid;
      QString title;
    };

    enum class RoleNames : int {
      IdRole = Qt::UserRole + 1,
      TitleRole = Qt::UserRole + 2
    };
    
    Q_ENUMS(RoleNames)

    Q_PROPERTY(QString category WRITE setCategory READ category)

    explicit SnippetEntryModel(QObject *parent = 0);
    
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void refresh();

    void setCategory(const QString& cat);
    QString category();
  
  protected:
    virtual QHash<int, QByteArray> roleNames() const override;

  private:
    QString m_category;
    QList<SnippetData> m_data;
    QHash<int, QByteArray> m_roleNames;
};

} // namespace kodew

#endif
