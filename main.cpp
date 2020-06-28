#include "mainwindow.h"
#include "menuwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    //MainWindow w;
    MenuWindow w;
    w.show();
    return a.exec();
}
