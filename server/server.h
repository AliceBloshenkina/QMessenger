#ifndef SERVER_H
#define SERVER_H

#include <QDataStream>
#include <QVector>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlError>
#include <QThreadPool>
#include <QRunnable>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "databasemanager.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

private slots:
    void slotNewConnection();
    void slotDisconnected();
    void slotTextMessageReceived(const QString &message);

private:
    QWebSocketServer *webSocketServer;
    QMap<QWebSocket*, QString> clients;
    DatabaseManager dbManager;

    void sendMessageToClients(const QJsonObject &jsonIncoming, QWebSocket *socket = nullptr, bool status = false);
    void handleLogin(QWebSocket* socket, const QJsonObject &jsonObj);
    void handleRegistration(QWebSocket* socket,const QJsonObject &jsonObj);
    void handleChatMessage(QWebSocket *socket, const QJsonObject &jsonObj);
    QJsonArray getOnlineClientsList(QWebSocket *socket);
    void notifyAllClients(const QString &newClientLogin, QWebSocket *socket, const QString &status);
    QString checkOnlineStatus(const QString &login);
};

#endif // SERVER_H
