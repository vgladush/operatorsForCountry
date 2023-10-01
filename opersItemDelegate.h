#ifndef OPERSITEMDELEGATE_H
#define OPERSITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QObject>

#define ICONSIZE 16
#define DELIM 3

class OpersItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
public:
    OpersItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void editRow(const QModelIndex &index);

public slots:
    void onButtonClicked(int mcc, int mnc);
};


#endif // OPERSITEMDELEGATE_H
