#ifndef DBWORKER_H
#define DBWORKER_H

#include <QSqlDatabase>
#include <QString>
#include <QList>

struct CountryOperators
{
    QString mcc;
    QString codeMnc;
    QString name;
    int length;
};

class DBWorker
{
public:
    DBWorker();
    ~DBWorker();

    bool init(QString path = "/home/gladush/projects/operators/system.db");
    QList<CountryOperators> countries();
    QList<CountryOperators> operatorsByMcc(const QString &mcc);
    CountryOperators countryByMcc(const QString &mcc);
    QString lastError();
    bool changeNameOperator(const CountryOperators &oper);
    bool addOperator(const CountryOperators &oper);
    bool isExistOperator(const CountryOperators &oper);

private:
    bool createCountriesTable();
    bool createOperatorsTable();
    QSqlDatabase    m_db;
    QString         m_error;
};

#endif // DBWORKER_H
