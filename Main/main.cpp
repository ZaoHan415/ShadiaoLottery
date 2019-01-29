#include "mainwindow.h"
#include <QApplication>
#include <string>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    MainWindow w(n1,n2);
    w.show();

    return a.exec();
}
