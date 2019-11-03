#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include "generated/NetObject_net.h"


namespace Ui {
class MainWindow;
}


QMainWindow* getMainWindow();


class NetObject
{
public:
    NetObject()
    {}

    void setPos(int32_t x, int32_t y)
    {
        btn->move(x, y);
    }

    void set_x(int32_t new_x)
    {
        btn->move(new_x, btn->y());
    }

    void set_y(int32_t new_y)
    {
        btn->move(btn->y(), new_y);
    }

    void set_button_name(const std::string& button)
    {
        btn = getMainWindow()->findChild<QPushButton*>(button.c_str());
    }

    int32_t get_x() const
    {
        return btn->x();
    }

    int32_t get_y() const
    {
        return btn->y();
    }

    std::string get_button_name() const
    {
        if (btn)
            return btn->objectName().toStdString();
        else
            return "";
    }

private:
    QPushButton* btn = nullptr;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(NetCoworkProvider* _provider, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bStart_clicked(bool checked);

private:
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    NetCoworkProvider* provider;
    NetObjectSync<QPushButton>* obj;
    NetObjectProcessor<QPushButton>* nop;
};

#endif // MAINWINDOW_H
