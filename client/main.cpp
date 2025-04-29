#include "enterwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnterWindow w;
    w.show();

    return a.exec();
}

