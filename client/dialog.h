#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTimer>
#include <QListWidget>
#include <QListWidgetItem>
#include "systemmessage.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void set_login(QString login, QString password);
    bool socketConnect(SystemMessage typeMessage);

signals:
    void onSuccess();
    void onError();
    void somethingWrong();
    void chooseUser();

private slots:
    void on_pushButton_clicked();
    void slotDisconnected();
    void slotTextMessageReceived(const QString &message);
    void onUserSelected(QListWidgetItem *item);
    void onSearchUsers_textEdited();

private:
    Ui::Dialog *ui;
    QString login;
    QString password;
    QString toLogin;
    QListWidgetItem *selectedUser;
    QWebSocket *socket;
    QListWidget *userDropdown = nullptr;
    QJsonArray history;
    QHash<QString, QListWidgetItem*> userItemMap;

    void SendToServer(QString str, QString toLogin);
    void handleClients(const QJsonArray &clients);
    void handleAddNewClient(const QJsonObject &newClient);
    void handleRemoveClient(const QJsonObject &client);
    void loadChatHistory(const QString &user);
    void onSearchUsers_dropdownAppend(const QJsonObject &client);
    void markMessagesAsRead(const QString &client);
    void handleLogin(const QJsonObject &jsonObj);
    void handleRegistration(const QJsonObject &jsonObj);
    void handleChat(const QJsonObject &jsonObj);
    void handleUpdateClients(const QJsonObject &jsonObj);
    void getOnlineStatus(const QJsonObject &jsonObj);
    void showInitialState();
    void restoreChatState();

};

#endif // DIALOG_H
