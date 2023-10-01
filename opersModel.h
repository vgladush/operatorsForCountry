#ifndef OPERSMODEL_H
#define OPERSMODEL_H

#include <QAbstractItemModel>

class OpersModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    OpersModel(QObject *parent);
    ~OpersModel();

    QObject *objByIndex(const QModelIndex& index) const;
    void insetrItem(QObject *item, const QModelIndex &parentIndex);
    void insetrItem(QObject *item);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void updateOperatorName(const QModelIndex &index, const QString &name);

private:
    QObject     *m_rootObj;
};

#endif // OPERSMODEL_H
