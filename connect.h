#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtSql>


class Connection : public QObject
{
    Q_OBJECT
public:

    explicit Connection(QObject *parent = 0);
    ~Connection();

    bool setConnection(QString &driver, QString &databasename, QString &hostname, QString &username, QString &passwd);
    bool rmConnection();
    void setDb(QSqlDatabase value);
    void setDatabasename(const QString &value);
    void setDriver(const QString &value);
    void setHostname(const QString &value);
    void setUsername(const QString &value);
    void setPasswd(const QString &value);


    QStringList getDrivers() const;


private:
    QSqlDatabase db;
    QString databasename;
    QString driver;
    QString hostname;
    QString username;
    QString passwd;

    QSqlDatabase getDb() const;
    QString getDatabasename() const;
    QString getUsername() const;
    QString getPasswd() const;
    QString getDriver() const;
    QString getHostname() const;

signals:

public slots:

};

#endif // CONNECTION_H
