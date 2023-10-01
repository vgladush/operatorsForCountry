#include "opersModel.h"

OpersModel::OpersModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_rootObj = new QObject(this);
}

OpersModel::~OpersModel()
{
}

QObject* OpersModel::objByIndex(const QModelIndex &index) const
{
    if(!index.isValid())
        return m_rootObj;

    return static_cast<QObject*>(index.internalPointer());
}

void OpersModel::insetrItem(QObject *item, const QModelIndex &parentIndex)
{
    beginInsertRows(parentIndex, rowCount(parentIndex), rowCount(parentIndex));
    item->setParent(objByIndex(parentIndex));
    endInsertRows();
}

void OpersModel::insetrItem(QObject *item)
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));

    for(auto row : m_rootObj->children())
    {
        if(row->property("mcc").toString() == item->property("mcc").toString())
        {
            item->setParent(row);
            break;
        }
    }

    endInsertRows();
}

QModelIndex OpersModel::index(int row, int column, const QModelIndex& parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column, objByIndex(parent)->children().at(row));
}

QModelIndex OpersModel::parent(const QModelIndex &child) const
{
    QObject *currentObj = objByIndex(child);
    QObject *parentObj = currentObj->parent();

    if(parentObj == m_rootObj)
        return QModelIndex();

    int row = parentObj->parent()->children().indexOf(parentObj);

    return createIndex(row, 0, parentObj);
}

int OpersModel::rowCount(const QModelIndex &parent) const
{
    return objByIndex(parent)->children().count();
}

int OpersModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant OpersModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
    {
        QHash<QString, QString> data;

        if(objByIndex(index)->parent() == m_rootObj)
            data.insert("code", objByIndex(index)->property("code").toString());
        else
            data.insert("mnc", objByIndex(index)->property("mnc").toString());

        data.insert("name", objByIndex(index)->property("objectName").toString());
        data.insert("mcc", objByIndex(index)->property("mcc").toString());

        return QVariant::fromValue(data);
    }
    else if(index.isValid() && role == Qt::EditRole) // якщо парент рут значить це країна
        return objByIndex(index)->parent() == m_rootObj;

    return QVariant();
}

void OpersModel::updateOperatorName(const QModelIndex &index, const QString &name)
{
    objByIndex(index)->setObjectName(name);
    dataChanged(index, index);
}
