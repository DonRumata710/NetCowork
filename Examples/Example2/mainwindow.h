#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include "generated/NetObject_net.h"


namespace Ui {
class MainWindow;
}


QMainWindow* getMainWindow();


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
    NetObjectSync<QPushButton>* obj = nullptr;
    NetObjectProcessor<QPushButton>* nop = nullptr;
};

#endif // MAINWINDOW_H
