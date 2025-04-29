#ifndef ENTERWINDOW_H
#define ENTERWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EnterWindow;
}
QT_END_NAMESPACE

enum Mode {LogIn, SignUp};

class EnterWindow : public QMainWindow
{
    Q_OBJECT


public:
    EnterWindow(QWidget *parent = nullptr);
    ~EnterWindow();

public slots:
    void slotOnSuccess();
    void slotOnError();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::EnterWindow *ui;
    Dialog *dialogWindow;
    Mode currentMode;
    void updateUI();

};
#endif // ENTERWINDOW_H
