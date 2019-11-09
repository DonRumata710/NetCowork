#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <netcoworkprovider.h>

#include <QMouseEvent>
#include <QApplication>

#include "game.h"


enum Pages
{
    START_PAGE,
    GAME_PAGE,
    OPTIONS_PAGE
};


QMainWindow* getMainWindow()
{
    for(QWidget *widget : qApp->topLevelWidgets())
        if (QMainWindow *mainWindow = qobject_cast<QMainWindow*>(widget))
            return mainWindow;
    return nullptr;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bStart_clicked()
{
    qobject_cast<Game*>(ui->stackedWidget->widget(GAME_PAGE))->start(port, address);
    ui->stackedWidget->setCurrentIndex(GAME_PAGE);
}

void MainWindow::on_bSettings_clicked()
{
    ui->stackedWidget->setCurrentIndex(OPTIONS_PAGE);
}

void MainWindow::on_bExit_clicked()
{
    QApplication::exit();
}

void MainWindow::on_buttonBox_accepted()
{
    if (ui->groupBox->isChecked())
        address = ui->address->text();
    else
        address.clear();

    port = ui->port->value();
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    ui->stackedWidget->setCurrentIndex(START_PAGE);
}

bool MainWindow::hasHeightForWidth() const
{
    return true;
}

int MainWindow::heightForWidth(int w) const
{
    return w;
}
