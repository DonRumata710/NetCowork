#include "mainwindow.h"

#include "netcoworkserver.h"
#include "netcoworkclient.h"

#include <QApplication>

#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
