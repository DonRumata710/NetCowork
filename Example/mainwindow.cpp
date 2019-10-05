#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>


QMainWindow* getMainWindow()
{
    for(QWidget *widget : qApp->topLevelWidgets())
        if (QMainWindow *mainWindow = qobject_cast<QMainWindow*>(widget))
            return mainWindow;
    return nullptr;
}


class NetObject : public iNetObject
{
public:
    NetObject()
    {}

    virtual void setPos(int32_t x, int32_t y) override
    {
        btn->move(x, y);
    }

    virtual void set_x(int32_t new_x) override
    {
        btn->move(new_x, btn->y());
    }

    virtual void set_y(int32_t new_y) override
    {
        btn->move(btn->y(), new_y);
    }

    virtual void set_button_name(const std::string& button) override
    {
        btn = getMainWindow()->findChild<QPushButton*>(button.c_str());
    }

    virtual int32_t get_x() const override
    {
        return btn->x();
    }

    virtual int32_t get_y() const override
    {
        return btn->y();
    }

    virtual std::string get_button_name() const override
    {
        if (btn)
            return btn->objectName().toStdString();
        else
            return "";
    }

private:
    QPushButton* btn = nullptr;
};


iNetObject* NetObjectProcessor::generate_object() const
{
    return new NetObject;
}


MainWindow::MainWindow(NetCoworkProvider* _provider, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    provider(_provider),
    nop(provider->register_new_class<NetObjectProcessor>())
{
    ui->setupUi(this);

    if (provider->is_server())
    {
        obj = nop->get_object();
        obj->set_button_name(ui->pushButton->objectName().toStdString());
    }
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
        obj->setPos(event->x(), event->y());
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
