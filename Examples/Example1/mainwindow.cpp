#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <netcoworkprovider.h>

#include <QMouseEvent>
#include <QApplication>


QMainWindow* getMainWindow()
{
    for(QWidget *widget : qApp->topLevelWidgets())
        if (QMainWindow *mainWindow = qobject_cast<QMainWindow*>(widget))
            return mainWindow;
    return nullptr;
}



template<>
QPushButton* NetObjectProcessor<QPushButton>::generate_object() const
{
    return getMainWindow()->findChild<QPushButton*>("pushButton");
}


MainWindow::MainWindow(NetCoworkProvider* _provider, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    provider(_provider),
    nop(provider->register_new_class<NetObjectProcessor<QPushButton>>())
{
    ui->setupUi(this);

    if (provider->is_server())
    {
        obj = nop->get_object();
    }

    provider->set_add_object_callback([this](NetCoworker* p_obj, uint32_t class_id, uint32_t obj_id){
        obj = dynamic_cast<decltype(obj)>(p_obj);
    });
}

MainWindow::~MainWindow()
{
    delete nop;
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (!obj)
    {
        return;
    }

    if (ui->pushButton->isChecked())
    {
        obj->move(event->pos());
    }
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::on_bStart_clicked(bool checked)
{
    if (checked)
        provider->start("127.0.0.1", 33333);
    else
        provider->stop();
}
