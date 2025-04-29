/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *centralwidget;
    QLabel *titleLabel;
    QListWidget *userListWidget;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit_3;
    QStatusBar *statusbar;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(530, 479);
        centralwidget = new QWidget(Dialog);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(0, 0, 530, 480));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(140, 10, 350, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);
        userListWidget = new QListWidget(centralwidget);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setGeometry(QRect(10, 60, 120, 410));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(140, 60, 350, 351));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 430, 290, 40));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(440, 430, 80, 40));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(10, 20, 113, 28));
        statusbar = new QStatusBar(Dialog);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 25));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Chat", nullptr));
        centralwidget->setStyleSheet(QCoreApplication::translate("Dialog", "\n"
"     background-color: #f5f5f5;\n"
"     font-family: Arial, sans-serif;\n"
"    ", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("Dialog", "\n"
"      color: #333;\n"
"      border-bottom: 2px solid #007BFF;\n"
"    ", nullptr));
        titleLabel->setText(QCoreApplication::translate("Dialog", "Chat Room", nullptr));
        userListWidget->setStyleSheet(QCoreApplication::translate("Dialog", "\n"
"      border: 1px solid #aaa;\n"
"      border-radius: 5px;\n"
"      background-color: #fff;\n"
"     ", nullptr));
        textBrowser->setStyleSheet(QCoreApplication::translate("Dialog", "\n"
"      border: 1px solid #aaa;\n"
"      border-radius: 5px;\n"
"      background-color: #fff;\n"
"      padding: 5px;\n"
"     ", nullptr));
        lineEdit->setStyleSheet(QCoreApplication::translate("Dialog", "\n"
"      border: 1px solid #aaa;\n"
"      border-radius: 5px;\n"
"      background-color: #fff;\n"
"      padding: 5px;\n"
"     ", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("Dialog", "Type your message...", nullptr));
        pushButton->setStyleSheet(QCoreApplication::translate("Dialog", "\n"
"      background-color: #007BFF;\n"
"      color: #fff;\n"
"      border: none;\n"
"      border-radius: 5px;\n"
"      padding: 10px;\n"
"     ", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "Send", nullptr));
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("Dialog", "Search ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
