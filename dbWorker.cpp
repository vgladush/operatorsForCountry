#include "dbWorker.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

DBWorker::DBWorker()
{
}

DBWorker::~DBWorker()
{
}

bool DBWorker::init(QString path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "system_db");
    m_db.setDatabaseName(path);
    m_db.setConnectOptions("QSQLITE_BUSY_TIMEOUT=5000");

    if(!m_db.open())
    {
        m_error = m_db.lastError().text();
        return false;
    }

    if(!createCountriesTable() || !createOperatorsTable())
        return false;

    return true;
}

QList<CountryOperators> DBWorker::countries()
{
    QList<CountryOperators> data;

    QSqlQuery query{m_db};
    query.setForwardOnly(true);
    query.prepare("SELECT * FROM `countries`;");

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return data;
    }

    while(query.next())
    {
        CountryOperators country;

        country.mcc = query.value("mcc").toString();
        country.codeMnc = query.value("code").toString();
        country.name = query.value("name").toString();

        data.append(country);
    }

    return data;
}

QList<CountryOperators> DBWorker::operatorsByMcc(const QString &mcc)
{
    QList<CountryOperators> data;

    QSqlQuery query{m_db};
    query.setForwardOnly(true);
    query.prepare("SELECT * FROM `operators` WHERE mcc = :mcc;");

    query.bindValue(":mcc", mcc);

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return data;
    }

    while(query.next())
    {
        CountryOperators operatorData;

        operatorData.codeMnc = query.value("mnc").toString();
        operatorData.name = query.value("name").toString();

        data.append(operatorData);
    }

    return data;
}

CountryOperators DBWorker::countryByMcc(const QString& mcc)
{
    CountryOperators country;
    QSqlQuery query{m_db};
    query.setForwardOnly(true);
    query.prepare("SELECT * FROM `countries` WHERE mcc = :mcc;");

    query.bindValue(":mcc", mcc);

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return CountryOperators();
    }

    if(query.next())
    {
        country.mcc = query.value("mcc").toString();
        country.codeMnc = query.value("code").toString();
        country.name = query.value("name").toString();
        country.length = query.value("mnc_length").toInt();
    }

    return country;
}

QString DBWorker::lastError()
{
    return m_error;
}

bool DBWorker::changeNameOperator(const CountryOperators& oper)
{
    QSqlQuery query{m_db};

    if(!m_db.transaction())
    {
        m_error = m_db.lastError().text();
        return false;
    }

    query.prepare("UPDATE `operators` "
                  " SET name = :name "
                  " WHERE mcc = :mcc AND mnc = :mnc; ");

    query.bindValue(":name", oper.name);
    query.bindValue(":mcc", oper.mcc);
    query.bindValue(":mnc", oper.codeMnc);

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return false;
    }

    if(!m_db.commit())
    {
        m_db.rollback();
        m_error = m_db.lastError().text();
        return false;
    }

    return true;
}

bool DBWorker::addOperator(const CountryOperators& oper)
{
    QSqlQuery query{m_db};

    if(!m_db.transaction())
    {
        m_error = m_db.lastError().text();
        return false;
    }

    query.prepare(" INSERT INTO `operators` "
                  " (name, mcc, mnc) "
                  " VALUES (:name, :mcc, :mnc);");

    query.bindValue(":name", oper.name);
    query.bindValue(":mcc", oper.mcc);
    query.bindValue(":mnc", oper.codeMnc);

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return false;
    }

    if(!m_db.commit())
    {
        m_error = m_db.lastError().text();
        return false;
    }

    return true;
}

bool DBWorker::isExistOperator(const CountryOperators& oper)
{
    QSqlQuery query{m_db};
    query.setForwardOnly(true);
    query.prepare("SELECT * FROM `operators` WHERE mcc = :mcc AND mnc = :mnc; ");

    query.bindValue(":mcc", oper.mcc);
    query.bindValue(":mnc", oper.codeMnc);

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return false;
    }

    if(query.next())
        return true;

    return false;
}

bool DBWorker::createCountriesTable()
{
    QSqlQuery query { "CREATE TABLE IF NOT EXISTS `countries` ("
                      " `mcc` INTEGER, "
                      " `code` TEXT, "
                      " `name` TEXT, "
                      " `mnc_length` INTEGER "
                      ");", m_db };

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return false;
    }

    return true;
}

bool DBWorker::createOperatorsTable()
{
    QSqlQuery query { "CREATE TABLE IF NOT EXISTS `operators` ( "
                      " `mcc` TEXT, "
                      " `mnc` TEXT, "
                      " `name` TEXT "
                      " );", m_db };

    if(!query.exec())
    {
        m_error = query.lastError().text();
        return false;
    }

    return true;
}
