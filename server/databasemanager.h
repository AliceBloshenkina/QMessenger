#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QWebSocket>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool openDatabase();
    void closeDatabase();

    bool initializeDatabase();
    bool userExists(const QString& login);
    bool addUser(const QString& login, const QString& password, const QString& salt);
    bool checkUserPassword(const QString& login, const QString& password);
    QJsonArray getMessages(const QString& login, const QMap<QWebSocket*, QString>& clients);
    void addMessage(const QString& from, const QString& to, const QString& message);
    void markMessagesAsRead(const QString &from, const QString &to, const QString& msgId = nullptr);
    QJsonArray getUsersByName(const QMap<QWebSocket*, QString> &clients, const QString &login, const QString &letters);
    bool executeQuery(const QString &queryString, const QMap<QString, QVariant> &params, QSqlQuery *query);
    QString generateSalt();
    QString hashPassword(const QString &password, const QString &salt);
    bool registrateNewClients(const QString &login, const QString &password);


private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
