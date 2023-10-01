#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

#include "opersItemDelegate.h"

OpersItemDelegate::OpersItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void OpersItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    if(!index.model()->data(index, Qt::DisplayRole).canConvert<QHash<QString, QString>>())
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QHash<QString, QString> data = index.model()->data(index, Qt::DisplayRole).value<QHash<QString, QString>>();

    QString name = data["name"];
    QString path;

    if(index.model()->data(index, Qt::EditRole).toBool())
        path = QString(":/Icons/%1.png").arg(data["code"]);
    else
    {
        name += " (" + data["mcc"] + ", " + data["mnc"] + ")";
        path = QString(":/Icons/%1_%2.png").arg(data["mcc"]).arg(data["mnc"]);
    }

    QRect rect = option.rect;

    if(QFile::exists(path))
    {
        QIcon icon(path);
        icon.paint(painter, rect.left(), rect.top(), ICONSIZE, ICONSIZE);
    }
    else
    {
        QIcon quest(QString(":/Icons/question.png"));
        quest.paint(painter, rect.left(), rect.top(), ICONSIZE, ICONSIZE);
    }

    rect.setLeft(rect.left() + ICONSIZE + DELIM);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, name);

    if(!index.model()->data(index, Qt::EditRole).toBool() && option.state & QStyle::State_MouseOver)
    {
        rect.setLeft(rect.left() + QFontMetrics(option.font).horizontalAdvance(name) + DELIM);

        QIcon plusIcon(":/Icons/plus.png");
        plusIcon.paint(painter, rect.left(), rect.top(), ICONSIZE, ICONSIZE);
    }
}

void OpersItemDelegate::onButtonClicked(int mcc, int mnc)
{
    // empty slot
    qDebug() << QString(" Plus pressed, mcc: %1, mnc: %2 ").arg(mcc).arg(mnc);
}

bool OpersItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(!index.model()->data(index, Qt::EditRole).toBool())
    {
        if(event->type() == QEvent::MouseButtonDblClick)
        {
            emit editRow(index);
            return true;
        }

        if(event->type() == QEvent::MouseButtonRelease)
        {
            if(!index.model()->data(index, Qt::DisplayRole).canConvert<QHash<QString, QString>>())
                return false;

            QHash<QString, QString> data = index.model()->data(index, Qt::DisplayRole).value<QHash<QString, QString>>();

            QRect buttonRect(option.rect.left() + QFontMetrics(option.font).horizontalAdvance(QString(data["name"] + " (" + data["mcc"] + ", " + data["mnc"] + ")")) + ICONSIZE + DELIM * 2,
                             option.rect.top(), ICONSIZE, ICONSIZE);

            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint mousePos = mouseEvent->pos();

            if(buttonRect.contains(mousePos))
            {
                emit onButtonClicked(data["mcc"].toInt(), data["mnc"].toInt());
                return true;
            }
        }
    }

    return false;
}
