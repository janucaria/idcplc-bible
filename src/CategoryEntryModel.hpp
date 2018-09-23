#ifndef KODEW_CATEGORY_ENTRY_MODEL_HPP
#define KODEW_CATEGORY_ENTRY_MODEL_HPP

#include <QtCore>

namespace kodew
{

class CategoryEntryModel : public QAbstractListModel
{
    Q_OBJECT
  public:
    explicit CategoryEntryModel(QObject *parent = 0);
    
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void refresh();

  private:
    QList<QString> m_data;
};

} // namespace kodew

#endif
