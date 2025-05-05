#include "server.h"
#include <QFile>

Server::Server(QObject *parent)
    : QObject(parent),
    webSocketServer(new QWebSocketServer(QStringLiteral("Chat Server"), QWebSocketServer::NonSecureMode, this)),
    dbManager()
{
    if (webSocketServer->listen(QHostAddress::Any, 1111)){
        qDebug() << "Server started";
        connect(webSocketServer, &QWebSocketServer::newConnection, this, &Server::slotNewConnection);

    } 
}

void Server::slotNewConnection()
{

    QWebSocket *socket = webSocketServer->nextPendingConnection();
    if(!socket){
        return;
    }

    connect(socket, &QWebSocket::textMessageReceived, this, &Server::slotTextMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &Server::slotDisconnected);

}

void Server::slotTextMessageReceived(const QString &message)
{
    QWebSocket *socket = qobject_cast<QWebSocket*>(sender());
    if (!socket){
        return;
    }

    QJsonDocument docJson = QJsonDocument::fromJson(message.toUtf8());
    if(!docJson.isObject()){
        return;
    }

    QJsonObject jsonObj = docJson.object();

    QString typeMessage = jsonObj["type"].toString();

    if (typeMessage == "login") {
        handleLogin(socket, jsonObj);
    } else if (typeMessage == "registration"){
        handleRegistration(socket, jsonObj);
    } else if (typeMessage == "chat") {
        handleChatMessage(socket, jsonObj);
    } else if (typeMessage == "search_users") {
        sendMessageToClients(jsonObj, socket);
    } else if (typeMessage == "get_online_status") {
        jsonObj["online"] = checkOnlineStatus(jsonObj["message"].toString());
        sendMessageToClients(jsonObj, socket);
    } else if (typeMessage == "mark_as_read"){
        dbManager.markMessagesAsRead(jsonObj["from"].toString(), jsonObj["to"].toString());
    } else if (typeMessage == "ack") {
        dbManager.markMessagesAsRead(jsonObj["from"].toString(), jsonObj["to"].toString(), jsonObj["msg_id"].toString());
    } 
}

void Server::handleLogin(QWebSocket* socket, const QJsonObject &jsonObj)
{
    if (!socket || jsonObj["login"].toString().isEmpty() || jsonObj["password"].toString().isEmpty()) {
        return;
    }

    bool statusLogin = dbManager.checkUserPassword(jsonObj["login"].toString(), jsonObj["password"].toString());

    if(statusLogin){
        clients.insert(socket, jsonObj["login"].toString());
        notifyAllClients(jsonObj["login"].toString(), socket, "TRUE");
    }
    sendMessageToClients(jsonObj, socket, statusLogin);
}



void Server::handleRegistration(QWebSocket* socket, const QJsonObject &jsonObj)
{
    if (!socket || jsonObj["login"].toString().isEmpty() || jsonObj["password"].toString().isEmpty()) {
        return;
    }

    bool statusRegistartion = dbManager.registrateNewClients(jsonObj["login"].toString(), jsonObj["password"].toString());
    clients.insert(socket, jsonObj["login"].toString());
    sendMessageToClients(jsonObj, socket, statusRegistartion);
    if(statusRegistartion){
        clients.insert(socket, jsonObj["login"].toString());
        notifyAllClients(jsonObj["login"].toString(), socket, "TRUE");

    }
}

void Server::handleChatMessage(QWebSocket *socket, const QJsonObject &jsonObj)
{
    QString toLogin = jsonObj["to"].toString();
    QWebSocket *recipientSocket = clients.key(toLogin, nullptr);

    dbManager.addMessage(jsonObj["from"].toString(), jsonObj["to"].toString(), jsonObj["message"].toString());

    if (recipientSocket) {
        sendMessageToClients(jsonObj, socket);
    } 
}

QString Server::checkOnlineStatus(const QString &login)
{
   for (auto it = clients.begin(); it != clients.end(); ++it) {
        if (it.value() == login) {
            return "TRUE";
        }
    }
    return "FALSE";
}



void Server::slotDisconnected()
{
    QWebSocket *socket = qobject_cast<QWebSocket*>(sender());
    if (!socket)
        return;

    if (clients.contains(socket)) {
        notifyAllClients(clients[socket], socket, "FALSE");
        clients.remove(socket);
    }
    socket->deleteLater();
}

QJsonArray Server::getOnlineClientsList(QWebSocket *socket) {
    QJsonArray onlineClients;

    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if(socket != it.key()){
            QJsonObject client;
            client["login"] = it.value();
            onlineClients.append(client);
        }
    }

    return onlineClients;
}

void Server::sendMessageToClients(const QJsonObject &jsonIncoming, QWebSocket *socket, bool status)
{
    QString messageType = jsonIncoming["type"].toString();

    QJsonObject response;

    if (messageType == "login"){
        response["type"] = "login";
        response["to"] = jsonIncoming["login"];
        response["status"] = status ? "success" : "fail";
        response["message"] = status ? "Login successful" : "Invalid login or password";

        if(status){
            response["history_messages"] = dbManager.getMessages(jsonIncoming["login"].toString(), clients);
        }

    } else if (messageType == "registration") {
        response["type"] = "registration";
        response["to"] = jsonIncoming["login"];
        response["status"] = status ? "success" : "fail";
        response["message"] = status ? "Registration successful" : "Login is used, please try again";

    } else if (messageType == "chat") {

        response["type"] = "chat";
        response["from"] = jsonIncoming["from"];
        response["to"] = jsonIncoming["to"];
        response["message"] = jsonIncoming["message"];


        QWebSocket *tempSocket = clients.key(response["to"].toString(), nullptr);
        if (tempSocket){
            socket = tempSocket;
            response["status"] = "success";
        } else {
            response["status"] = "fail";
            response["message"] = "Client not found!";
        }
    } else if (messageType == "search_users") {
        response["type"] = "search_users";
        response["to"] = jsonIncoming["login"];
        response["clients"] = dbManager.getUsersByName(clients, jsonIncoming["login"].toString(), jsonIncoming["message"].toString());
    } else if (messageType == "get_online_status"){
        response["type"] = "get_online_status";
        response["to"] = jsonIncoming["login"];
        response["online"] = jsonIncoming["online"];
        response["message"] = jsonIncoming["message"];
    } 

    QJsonDocument doc(response);
    socket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));


}

void Server::notifyAllClients(const QString &newClientLogin, QWebSocket *socket, const QString &status) {
    QJsonObject notification;
    notification["type"] = "update_clients";
    notification["login"] = newClientLogin;
    notification["online"] = status;

    QJsonDocument doc(notification);
    QString message = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));

    for (QWebSocket *clientSocket : clients.keys()) {
        if (clientSocket && clientSocket != socket) {
            clientSocket->sendTextMessage(message);
        } 
    }
}



