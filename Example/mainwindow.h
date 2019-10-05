#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "netobject.h"
#include "netobjectprocessor.h"


namespace Ui {
class MainWindow;
}

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
    iNetObject* obj;
    NetObjectProcessor* nop;
};

#endif // MAINWINDOW_H
