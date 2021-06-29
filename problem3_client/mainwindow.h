#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <windows.h>
#include <QMessageBox>
#include <QDebug>
#include "pokemon.h"
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
    bool fighting();
    void showInformation();
    void showInformationOfUser();
    bool hasIllegal(QString s);

private slots:
    void socket_disconnected();
    void readData();
    // 注册按钮
    void on_regist_button_clicked();
    // 登录按钮
    void on_login_button_clicked();
    // 查看下一个小精灵按钮
    void on_next_clicked();
    // 寻找对手按钮
    void on_search_clicked();
    // 升级赛按钮
    void on_pushButton_lvUpBattle_clicked();
    // 决斗赛按钮
    void on_pushButton_battle_clicked();
    // 升级按钮
    void on_levelup_clicked();
    // 送出宠物1按钮
    void on_send1_clicked();
    // 送出宠物2按钮
    void on_send2_clicked();
    // 送出宠物3按钮
    void on_send3_clicked();
    // 查看下一个小精灵按钮
    void on_next_2_clicked();
    // 战斗按钮
    void on_battle_clicked();
    // 返回按钮
    void on_back_clicked();
    // 登出按钮
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    // 下列数据结构定义与综合题目二一致
    QTcpSocket *socket;
    QString IP;
    int port;

    int select;
    unsigned int nowPokemon;
    player user;
    pokemonBase *p;

};
#endif // MAINWINDOW_H
