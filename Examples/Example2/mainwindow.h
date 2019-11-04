#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <netcoworkprovider.h>

#include <QMainWindow>
#include <QAbstractButton>
#include <QHostAddress>


namespace Ui {
class MainWindow;
}


QMainWindow* getMainWindow();


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bStart_clicked();

    void on_bSettings_clicked();

    void on_bExit_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::MainWindow *ui;

    QHostAddress address;
};

#endif // MAINWINDOW_H
