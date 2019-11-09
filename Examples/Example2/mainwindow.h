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
    virtual bool hasHeightForWidth() const override;
    virtual int heightForWidth(int w) const override;

private:
    Ui::MainWindow *ui;

    QString address = "localhost";
    uint16_t port = 1024;
};

#endif // MAINWINDOW_H
