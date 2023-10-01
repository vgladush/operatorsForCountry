#ifndef OPERSPOPUPDIALOG_H
#define OPERSPOPUPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "dbWorker.h"

class OpersPopupDialog : public QDialog
{
    Q_OBJECT

public:
    OpersPopupDialog(DBWorker &db, const QHash<QString, QString> &data, QWidget *parent = nullptr);

    // Методи доступу до значень полів введення
    QString name() const { return m_name->text(); }
    QString mcc() const { return m_mcc->text(); }
    QString mnc() const { return m_mnc->text(); }

public slots:
    void onCheckForm();

private:
    QLineEdit   *m_name;
    QLineEdit   *m_mcc;
    QLineEdit   *m_mnc;
    QPushButton *m_save;
    QPushButton *m_cancel;
    QLabel      *m_iconCountry;
    QLabel      *m_iconOper;
    DBWorker    &m_db;
};

#endif // OPERSPOPUPDIALOG_H
