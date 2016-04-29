#include "connect.h"
#include <QDebug>
#include <QSqlQuery>



Connection::Connection(QObject *parent) :
    QObject(parent)
{
    qDebug() << "instanciation Connection";
}

Connection::~Connection()
{
    db.close();
    qDebug() << "Destruction connection";
}

QString Connection::getDriver() const
{
    return driver;
}

void Connection::setDriver(const QString &value)
{
    driver = value;
}

QString Connection::getDatabasename() const
{
    return databasename;
}

void Connection::setDatabasename(const QString &value)
{
    databasename = value;
}

QString Connection::getHostname() const
{
    return hostname;
}

void Connection::setHostname(const QString &value)
{
    hostname = value;
}
QString Connection::getUsername() const
{
    return username;
}

void Connection::setUsername(const QString &value)
{
    username = value;
}
QString Connection::getPasswd() const
{
    return passwd;
}

void Connection::setPasswd(const QString &value)
{
    passwd = value;
}

QStringList Connection::getDrivers() const
{
    QStringList drivers = QSqlDatabase::drivers();
    return drivers;
}


bool Connection::setConnection(QString &driver, QString &databasename, QString &hostname, QString &username, QString &passwd)
{
    rmConnection();
    db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(databasename);
    db.setHostName(hostname);
    db.setUserName(username);
    db.setPassword(passwd);

    if(!db.open()) {
        return false;
    } else {
        return true;
    }
}

bool Connection::rmConnection()
{
    if(!db.contains("qt_sql_default_connection"))
        return false;
    db.close();
    return true;
}
