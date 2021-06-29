#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <windows.h>
#include "database.h"
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newConnect();
    void socketReadData();
    void socketDisconnected();

    Database playerDatabase;
    vector<player*> inLinePlayer;

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;

    int port;
};

QString get(const QByteArray &b , int &pos);
bool nameIsInDatabase(QByteArray &b , Database &playerDatabase);
bool infoIsInDatabase(QByteArray &b , Database &playerDatabase);

#endif // MAINWINDOW_H
