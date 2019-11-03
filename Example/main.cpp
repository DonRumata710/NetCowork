#include "mainwindow.h"

#include "netcoworkserver.h"
#include "netcoworkclient.h"

#include <QApplication>

#include <iostream>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "server or client?";
        return 1;
    }

    QApplication a(argc, argv);

    NetCoworkProvider* provider;
    QHostAddress addr("localhost");
    if (strcmp(argv[1], "server") == 0)
    {
        provider = new NetCoworkServer();
    }
    else
    {
        provider = new NetCoworkClient();
    }
    MainWindow w(provider);
    w.show();

    return a.exec();
}
