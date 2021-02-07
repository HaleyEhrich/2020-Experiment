#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString str;
    MainWindow w;
    w.show();
    w.welcomePage();
    return a.exec();
}
