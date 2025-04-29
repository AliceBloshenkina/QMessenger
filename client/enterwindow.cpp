#include "enterwindow.h"
#include "ui_enterwindow.h"
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "dialog.h"
#include <QDebug>
#include "systemmessage.h"


EnterWindow::EnterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnterWindow)
    , dialogWindow(nullptr)
    , currentMode(LogIn)
{
    ui->setupUi(this);
    updateUI();

}

EnterWindow::~EnterWindow()
{
    delete ui;
}

void EnterWindow::slotOnSuccess()
{
    dialogWindow->setModal(true);
    hide();
    dialogWindow->show();
    // show();
}

void EnterWindow::slotOnError()
{
    // сделать вывод на экран об ошибки
    qDebug() << "Ошибка на экран";
    if(currentMode == LogIn){
        ui->statusLabel->setText("Invalid login or password. Please try again.");
    } else {
        ui->statusLabel->setText("This login is already taken.");
    }
}

void EnterWindow::on_pushButton_clicked()
{

    ui->statusLabel->clear();
    if (dialogWindow) {
        delete dialogWindow;
    }

    dialogWindow = new Dialog(this);


    connect(dialogWindow, &Dialog::onSuccess, this, &EnterWindow::slotOnSuccess);
    connect(dialogWindow, &Dialog::onError, this, &EnterWindow::slotOnError);
    connect(dialogWindow, &QDialog::finished, this, &EnterWindow::show);

    dialogWindow->set_login(ui->lineEdit->text(), ui->lineEdit_2->text());

    if (currentMode == LogIn){
        dialogWindow->socketConnect(SystemMessage::Login);
    } else {
        dialogWindow->socketConnect(SystemMessage::Registration);
    }

    // dialogWindow->dumpObjectInfo();

}



void EnterWindow::on_pushButton_2_clicked()
{
    currentMode = (currentMode == LogIn) ? SignUp : LogIn; // Переключаем режим
    updateUI();
}

void EnterWindow::updateUI()
{
    if (currentMode == LogIn) {
        ui->titleLabel->setText("Welcome Back");
        ui->lineEdit->setPlaceholderText("Enter your login");
        ui->lineEdit_2->setPlaceholderText("Enter your password");
        ui->pushButton->setText("Log In");
        ui->pushButton_2->setText("Sign Up");
    } else {
        ui->titleLabel->setText("Create Account");
        ui->lineEdit->setPlaceholderText("Choose a login");
        ui->lineEdit_2->setPlaceholderText("Choose a password");
        ui->pushButton->setText("Sign Up");
        ui->pushButton_2->setText("Log In");
    }
}


