#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();

    // 连接信号槽，设置监听函数
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readData);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_disconnected);

    IP = "127.0.0.1";
    port = 6666;
    nowPokemon = 0;
    setFixedSize(900,600);
    takeCentralWidget();
    setCentralWidget(ui->login);

    // 设置图片背景，自适应大小
    QPalette PAllbackground = this->palette();
    //QImage ImgAllbackground(":/../pictures/login.jpg");
    QImage ImgAllbackground(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/login.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}


MainWindow::~MainWindow()
{
    delete this->socket;
    delete ui;
}

bool MainWindow::hasIllegal(QString s)
{
    for(int i = 0 ; i < s.size() ; i++){
        if((s[i] >= 'a' && s[i] <= 'z')
         ||(s[i] >= 'A' && s[i] <= 'Z')
         ||(s[i] >= '0' && s[i] <= '9')){

        }
        else{
            return true;
        }
    }
    return false;
}

void MainWindow::readData()
{
    QByteArray buffer;
    buffer = socket->readAll();
    if(!buffer.isEmpty()){
        int pos = 0;
        QString buf = get(buffer,pos);
        if(buf == userNameIsIn){
            qDebug() << "user name is in";
            QMessageBox::about(this,"warning","The username already exists.");
        }
        else if(buf == registSucceeded){
            qDebug() << "registe successful";
            qDebug() << buffer;
            QMessageBox::about(this," ","Register successfully.");
        }
        else if(buf == loginFailed){
            QMessageBox::about(this," ","Wrong user name or password.");
        }
        else if(buf == loginSucceeded){
            takeCentralWidget();
            setCentralWidget(ui->userinfo);

            QPalette PAllbackground = this->palette();
            QImage ImgAllbackground(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/start.jpg");
            QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
            PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
            this->setPalette(PAllbackground);

            user.getPlayerInfo(buffer,pos);
            get(buffer,pos);
            int x = 0;
            ui->tableWidget->setRowCount(50);
            ui->tableWidget->setColumnCount(9);
            ui->tableWidget->resizeColumnsToContents();
            ui->tableWidget->resizeColumnsToContents();
            while(pos < buffer.size()){
                player p;
                p.getOtherPlayer(buffer,pos);
                get(buffer,pos);
                ui->tableWidget->setItem(x,0,new QTableWidgetItem(p.getName(),0));
                ui->tableWidget->item(x,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->tableWidget->setItem(x,1,new QTableWidgetItem(p.getWinRate(),0));
                ui->tableWidget->item(x,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                for(int i = 0;i < p.getPetNum();i++){
                    ui->tableWidget->setItem(x,2,new QTableWidgetItem(p.petOfPlayer[i]->getName(),0));
                    if(user.petOfPlayer[i]->getName() == pokemonName[0]){
                        ui->tableWidget->setItem(x, 2, new QTableWidgetItem(QIcon(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/charmander.png"), "Charmander"));
                    }
                    else if(user.petOfPlayer[i]->getName() == pokemonName[1]){
                        ui->tableWidget->setItem(x, 2, new QTableWidgetItem(QIcon(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/squirtle.png"), "Squirtle"));
                    }
                    else if(user.petOfPlayer[i]->getName() == pokemonName[2]){
                        ui->tableWidget->setItem(x, 2, new QTableWidgetItem(QIcon(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/bulbasaur.png"), "Bulbasaur"));
                    }
                    else if(user.petOfPlayer[i]->getName() == pokemonName[3]){
                        ui->tableWidget->setItem(x, 2, new QTableWidgetItem(QIcon(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/pikachu.jpg"), "Pikachu"));
                    }
                    ui->tableWidget->setItem(x,3,new QTableWidgetItem(QString::number(p.petOfPlayer[i]->getGrade()),0));
                    ui->tableWidget->item(x,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(x,4,new QTableWidgetItem(QString::number(p.petOfPlayer[i]->getLv()),0));
                    ui->tableWidget->item(x,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(x,5,new QTableWidgetItem(QString::number(p.petOfPlayer[i]->getAtk()),0));
                    ui->tableWidget->item(x,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(x,6,new QTableWidgetItem(QString::number(p.petOfPlayer[i]->getDef()),0));
                    ui->tableWidget->item(x,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(x,7,new QTableWidgetItem(QString::number(p.petOfPlayer[i]->getHp()),0));
                    ui->tableWidget->item(x,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(x,8,new QTableWidgetItem(QString::number(1000 - p.petOfPlayer[i]->getSpd()),0));
                    ui->tableWidget->item(x,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    x++;
                }
                ui->tableWidget->setSpan(x-p.getPetNum(),0,p.getPetNum(),1);

                ui->tableWidget->setSpan(x-p.getPetNum(),1,p.getPetNum(),1);
                qDebug()<<p.toQString();
            }
            showInformationOfUser();

        }

    }
    socket_disconnected();
}

void MainWindow::showInformation()
{
    ui->label_username->setText(user.getName());
    // 显示胜率
    if(user.getWinNum() == 0 && user.getFailNum() == 0){
        //ui->lineEdit_winRate->setText("winRate: 0%");
    }
    else{
        //int winRate = (user.getWinNum() * 100) / ( user.getFailNum() + user.getWinNum());
        //ui->lineEdit_winRate->setText("winRate: " + QString::number(winRate,10) + "%");
    }
    // 显示宠物数量奖章
    if(user.getPetNum() >= 5){
        //ui->label_model->setText("Gold medal");
        ui->label_model->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/goldModal.jpg"));
    }
    else if(user.getPetNum() >= 3){
        ui->label_model->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/silverMedal.jpg"));
    }
    else{
        ui->label_model->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/bronzeModal.jpg"));
    }
    // 显示宠物质量奖章
    if(user.getHighPetNUm() >= 3){
        //ui->label_model->setText("Gold medal");
        ui->label_model_15->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/g15m.png"));
    }
    else if(user.getHighPetNUm() == 1){
        ui->label_model_15->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/s15m.png"));
    }
    else{
        ui->label_model_15->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/b15m.png"));
    }

    // 显示当前宠物信息
    ui->lineEdit_nowPet->setText(QString::number(nowPokemon+1,10) + "/" + QString::number(user.getPetNum(),10));
    if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[0]){
        ui->label_pet1->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/charmander.png"));
    }
    else if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[1]){
        ui->label_pet1->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/squirtle.png"));
    }
    else if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[2]){
        ui->label_pet1->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/bulbasaur.png"));
    }
    else if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[3]){
        ui->label_pet1->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/pikachu.jpg"));
    }
    switch(user.petOfPlayer[nowPokemon]->getGrade()){
    case GRAY:
        ui->lineEdit_name1->setStyleSheet("color:gray");
        break;
    case BLUE:
        ui->lineEdit_name1->setStyleSheet("color:blue");
        break;
    case PURPLE:
        ui->lineEdit_name1->setStyleSheet("color:magenta");
        break;
    case PINK:
        ui->lineEdit_name1->setStyleSheet("color:red");
        break;
    case GOLDEN:
        ui->lineEdit_name1->setStyleSheet("color:yellow");
        break;
    default:
        break;
    }
    ui->lineEdit_name1->setText(user.petOfPlayer[nowPokemon]->getName());
    ui->lineEdit_kind1->setText("kind: " + QString::number(user.petOfPlayer[nowPokemon]->getKind(),10));
    ui->lineEdit_lv1->setText("lv: " + QString::number(user.petOfPlayer[nowPokemon]->getLv(),10));
    ui->lineEdit_xp1->setText("xp: " + QString::number(user.petOfPlayer[nowPokemon]->getXp(),10) + "/" + QString::number(user.petOfPlayer[nowPokemon]->getXpMax(),10));
    ui->lineEdit_hp1->setText("hp: " + QString::number(user.petOfPlayer[nowPokemon]->getHp(),10));
    ui->lineEdit_atk1->setText("atk: " + QString::number(user.petOfPlayer[nowPokemon]->getAtk(),10));
    ui->lineEdit_def1->setText("def: " + QString::number(user.petOfPlayer[nowPokemon]->getDef(),10));
    ui->lineEdit_spd1->setText("spd: " + QString::number(1000 - user.petOfPlayer[nowPokemon]->getSpd(),10));
}

// 以下函数的功能和showInfoemation完全类似
void MainWindow::showInformationOfUser()
{
    //显示人物信息
    ui->lineEdit_username->setText(user.getName());
    //显示win rate
    if(user.getWinNum() == 0 && user.getFailNum() == 0){
        //ui->lineEdit_winRate->setText("winRate: 0%");
    }
    else{
        //int winRate = (user.getWinNum() * 100) / ( user.getFailNum() + user.getWinNum());
        //ui->lineEdit_winRate->setText("winRate: " + QString::number(winRate,10) + "%");
    }

    if(user.getPetNum() >= 5){
        //ui->label_model->setText("Gold medal");
        ui->label_4->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/goldModal.jpg"));
    }
    else if(user.getPetNum() >= 3){
        ui->label_4->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/silverMedal.jpg"));
    }
    else{
        ui->label_4->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/bronzeModal.jpg"));
    }

    if(user.getHighPetNUm() >= 3){
        //ui->label_model->setText("Gold medal");
        ui->label_5->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/g15m.png"));
    }
    else if(user.getPetNum() == 1){
        ui->label_5->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/s15m.png"));
    }
    else{
        ui->label_5->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/b15m.png"));
    }

    //显示当前宠物信息
    ui->lineEdit_nowPet_2->setText(QString::number(nowPokemon+1,10) + "/" + QString::number(user.getPetNum(),10));
    if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[0]){
        ui->userPetPic->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/charmander.png"));
    }
    else if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[1]){
        ui->userPetPic->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/squirtle.png"));
    }
    else if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[2]){
        ui->userPetPic->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/bulbasaur.png"));
    }
    else if(user.petOfPlayer[nowPokemon]->getName() == pokemonName[3]){
        ui->userPetPic->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/pikachu.jpg"));
    }
    switch(user.petOfPlayer[nowPokemon]->getGrade()){
    case GRAY:
        ui->lineEdit_name->setStyleSheet("color:gray");
        break;
    case BLUE:
        ui->lineEdit_name->setStyleSheet("color:blue");
        break;
    case PURPLE:
        ui->lineEdit_name->setStyleSheet("color:magenta");
        break;
    case PINK:
        ui->lineEdit_name->setStyleSheet("color:red");
        break;
    case GOLDEN:
        ui->lineEdit_name->setStyleSheet("color:yellow");
        break;
    default:
        break;
    }
    ui->lineEdit_name->setText(user.petOfPlayer[nowPokemon]->getName());
    ui->lineEdit_kind->setText("kind: " + QString::number(user.petOfPlayer[nowPokemon]->getKind(),10));
    ui->lineEdit_lv->setText("lv: " + QString::number(user.petOfPlayer[nowPokemon]->getLv(),10));
    ui->lineEdit_xp->setText("xp: " + QString::number(user.petOfPlayer[nowPokemon]->getXp(),10) + "/" + QString::number(user.petOfPlayer[nowPokemon]->getXpMax(),10));
    ui->lineEdit_hp->setText("hp: " + QString::number(user.petOfPlayer[nowPokemon]->getHp(),10));
    ui->lineEdit_atk->setText("atk: " + QString::number(user.petOfPlayer[nowPokemon]->getAtk(),10));
    ui->lineEdit_def->setText("def: " + QString::number(user.petOfPlayer[nowPokemon]->getDef(),10));
    ui->lineEdit_spd->setText("spd: " + QString::number(1000 - user.petOfPlayer[nowPokemon]->getSpd(),10));
}

// 关闭socket连接
void MainWindow::socket_disconnected()
{
    socket->close();
}

// 关闭登录按钮
void MainWindow::on_regist_button_clicked()
{
    socket->connectToHost(IP,port);
    if(!socket->waitForConnected(30000)){
        qDebug() << "Connection Failed !";
    }
    QByteArray sum;
    sum.clear();
    sum.append('r');
    QByteArray inName;
    QByteArray inPassword;
    inName.append(ui->name->text());
    inPassword.append(ui->password->text());

    if(hasIllegal(inName) || hasIllegal(inPassword)){
        QMessageBox::about(this,"Illegal input","The user name and password can only consist of letters and numbers.");
    }
    else{
        sum.append(inName);
        sum.append(' ');
        sum.append(inPassword);
        socket->write(sum);
    }
}

// 登录按钮
void MainWindow::on_login_button_clicked()
{
    socket->connectToHost(IP,port);
    if(!socket->waitForConnected(30000)){
        qDebug() << "Connection Failed !";
    }

    QByteArray sum;
    sum.clear();
    sum.append('l');
    QByteArray inName;
    QByteArray inPassword;
    inName.append(ui->name->text());
    inPassword.append(ui->password->text());
    if(hasIllegal(inName) || hasIllegal(inPassword)){
        QMessageBox::about(this,"Illegal input","The user name and password can only consist of letters and numbers.");
    }
    else{
        sum.append(inName);
        sum.append(' ');
        sum.append(inPassword);

        socket->write(sum);
    }
}

// 查看下一个宠物按钮
void MainWindow::on_next_clicked()
{
    nowPokemon++;
    if(nowPokemon >= user.getPetOfPlayer()){
        nowPokemon = 0;
    }
    showInformation();
}

// 寻找对手按钮
void MainWindow::on_search_clicked()
{
    int r = randNumber(0,3);
    switch(r){
    case 0:
        p = new Charmandar(ATK,"Charmandar",lvInit);
        break;
    case 1:
        p = new Squirtle(DEF,"Squirtle",lvInit);
        break;
    case 2:
        p = new Bulbasaur(HP,"Bulbasaur",lvInit);
        break;
    case 3:
        p = new Pikachu(SPD,"Pikachu",lvInit);
        break;
    default:
        break;
    }

    //显示当前宠物信息
    if(p->getName() == pokemonName[0]){
        ui->label_pet2->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/charmander.png"));
    }
    else if(p->getName() == pokemonName[1]){
        ui->label_pet2->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/squirtle.png"));
    }
    else if(p->getName() == pokemonName[2]){
        ui->label_pet2->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/bulbasaur.png"));
    }
    else if(p->getName() == pokemonName[3]){
        ui->label_pet2->setPixmap(QPixmap(":/new/prefix1/C:/Users/91917/OneDrive/桌面/pictures/pikachu.jpg"));
    }
    switch(p->getGrade()){
    case GRAY:
        ui->lineEdit_name2->setStyleSheet("color:gray");
        break;
    case BLUE:
        ui->lineEdit_name2->setStyleSheet("color:blue");
        break;
    case PURPLE:
        ui->lineEdit_name2->setStyleSheet("color:purple");
        break;
    case PINK:
        ui->lineEdit_name2->setStyleSheet("color:red");
        break;
    case GOLDEN:
        ui->lineEdit_name2->setStyleSheet("color:yellow");
        break;
    default:
        break;
    }
    ui->lineEdit_name2->setText(p->getName());
    ui->lineEdit_kind2->setText("kind: " + QString::number(p->getKind(),10));
    ui->lineEdit_lv2->setText("lv: " + QString::number(p->getLv(),10));
    ui->lineEdit_xp2->setText("xp: " + QString::number(p->getXp(),10) + "/" + QString::number(user.petOfPlayer[nowPokemon]->getXpMax(),10));
    ui->lineEdit_hp2->setText("hp: " + QString::number(p->getHp(),10));
    ui->lineEdit_atk2->setText("atk: " + QString::number(p->getAtk(),10));
    ui->lineEdit_def2->setText("def: " + QString::number(p->getDef(),10));
    ui->lineEdit_spd2->setText("spd: " + QString::number(p->getSpd(),10));

}

// 升级赛按钮
void MainWindow::on_pushButton_lvUpBattle_clicked()
{
    if(fighting()){
        user.win();
    }
    else{
        user.fail();
    }
    ui->lineEdit_xp1->setText("xp: " + QString::number(user.petOfPlayer[nowPokemon]->getXp(),10) + "/" + QString::number(user.petOfPlayer[nowPokemon]->getXpMax(),10));
}



void MainWindow::on_pushButton_battle_clicked()
{
    // 获胜之后获得战胜的小精灵
    if(fighting()){
        user.petOfPlayer.push_back(p);
        user.changePetNum(user.getPetNum()+1);
        user.win();
    }
    // 失败之后送出自己的小精灵
    else{
        user.fail();
        takeCentralWidget();
        setCentralWidget(ui->sendout);
        QMessageBox::about(this,"","Please choose one to throw!");
        ui->send1->setText(user.petOfPlayer[0]->getName());
        ui->lineEdit_lv_1->setText("lv:" + QString::number(user.petOfPlayer[0]->getLv(),10));
        ui->lineEdit_xp_1->setText("xp:" + QString::number(user.petOfPlayer[0]->getXp(),10));
        if(user.getPetNum() == 1){
            ui->send2->setEnabled(false);
            ui->send3->setEnabled(false);
        }
        else if(user.getPetNum() == 2){
            ui->send2->setText(user.petOfPlayer[1]->getName());
            ui->lineEdit_lv_2->setText("lv:" + QString::number(user.petOfPlayer[1]->getLv(),10));
            ui->lineEdit_xp_2->setText("xp:" + QString::number(user.petOfPlayer[1]->getXp(),10));
            ui->send3->setEnabled(false);
        }
        else{
            ui->send2->setText(user.petOfPlayer[1]->getName());
            ui->lineEdit_lv_2->setText("lv:" + QString::number(user.petOfPlayer[1]->getLv(),10));
            ui->lineEdit_xp_2->setText("xp:" + QString::number(user.petOfPlayer[1]->getXp(),10));
            select = randNumber(2,user.getPetNum()-1);
            ui->send3->setText(user.petOfPlayer[select]->getName());
            ui->lineEdit_lv_3->setText("lv:" + QString::number(user.petOfPlayer[select]->getLv(),10));
            ui->lineEdit_xp_3->setText("xp:" + QString::number(user.petOfPlayer[select]->getXp(),10));
            ui->send2->setEnabled(true);
            ui->send3->setEnabled(true);
        }

    }
}

// 战斗函数
bool MainWindow::fighting()
{
    user.petOfPlayer[nowPokemon]->fightStart();
    p->fightStart();
    int endFlag = 0;
    for(int i = user.petOfPlayer[nowPokemon]->getCspd() , j = p->getCspd() ; endFlag == 0 ; --i , --j){
        if(i == 0){
            i = user.petOfPlayer[nowPokemon]->getCspd();
            if(randNumber(1,100) > performRate){
                p->getAttacked(ui->textBrowser,*user.petOfPlayer[nowPokemon]);
            }
            else{
                user.petOfPlayer[nowPokemon]->useSkill(ui->textBrowser,*p);
            }
        }
        if(j == 0){
            j = p->getCspd();
            if(randNumber(1,100) > performRate){
                user.petOfPlayer[nowPokemon]->getAttacked(ui->textBrowser,*p);
            }
            else{
                p->useSkill(ui->textBrowser,*user.petOfPlayer[nowPokemon]);
            }
        }
        if(p->getChp() == 0){
            user.petOfPlayer[nowPokemon]->figheEnd(50);
            p->figheEnd(20);
            QMessageBox::about(this,"win","You win ! xp + 50");
            endFlag = 1;
            return true;
        }
        else if(user.petOfPlayer[nowPokemon]->getChp() == 0){
            p->figheEnd(50);
            user.petOfPlayer[nowPokemon]->figheEnd(20);
            QMessageBox::about(this,"fail","You fail! xp + 20");
            endFlag = 1;
            return false;
        }
    }
    return true;
}

// 升级按钮
void MainWindow::on_levelup_clicked()
{
    user.petOfPlayer[nowPokemon]->levelUp();

    showInformation();
}

// 送出第1个小精灵
void MainWindow::on_send1_clicked()
{
    takeCentralWidget();
    setCentralWidget(ui->user);

    if(user.getPetNum() == 1){
        user.petOfPlayer.pop_back();
        for(int i = 0 ; i < 3 ; ++i){
            int r = randNumber(0,3);
            pokemonBase *p;
            switch(r){
            case 0:
                p = new Charmandar(ATK,"Charmandar",lvInit);
                break;
            case 1:
                p = new Squirtle(DEF,"Squirtle",lvInit);
                break;
            case 2:
                p = new Bulbasaur(HP,"Bulbasaur",lvInit);
                break;
            case 3:
                p = new Pikachu(SPD,"Pikachu",lvInit);
                break;
            default:
                break;
            }
            user.petOfPlayer.push_back(p);
        }//end for(int i = 0 ; i < 3 ; ++i)
    }
    else{
        user.petOfPlayer.erase(user.petOfPlayer.begin(),user.petOfPlayer.begin() + 1);
    }
    user.changePetNum(user.petOfPlayer.size());
}

// 送出第2个小精灵
void MainWindow::on_send2_clicked()
{
    takeCentralWidget();
    setCentralWidget(ui->user);

    user.petOfPlayer.erase(user.petOfPlayer.begin()+1,user.petOfPlayer.begin()+2);
    user.changePetNum(user.petOfPlayer.size());
}

// 送出第3个小精灵
void MainWindow::on_send3_clicked()
{
    takeCentralWidget();
    setCentralWidget(ui->user);

    user.petOfPlayer.erase(user.petOfPlayer.begin()+select,user.petOfPlayer.begin()+select+1);
    user.changePetNum(user.petOfPlayer.size());
}

// 查看小精灵信息
void MainWindow::on_next_2_clicked()
{
    nowPokemon++;
    if(nowPokemon >= user.getPetOfPlayer()){
        nowPokemon = 0;
    }

    showInformationOfUser();
}

// 进入战斗界面
void MainWindow::on_battle_clicked()
{
    takeCentralWidget();
    setCentralWidget(ui->user);

    showInformation();
}

// 返回按钮，返回用户信息界面
void MainWindow::on_back_clicked()
{
    takeCentralWidget();
    setCentralWidget(ui->userinfo);

    showInformationOfUser();
}

// 登出按钮，上传更新信息
void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost(IP,port);
    if(!socket->waitForConnected(30000)){
        qDebug() << "Connection Failed !";
    }
    nowPokemon = 0;
    QString temp;
    temp.clear();
    temp += "o";
    temp += user.toQString();
    socket->write(temp.toUtf8());
    unsigned int x = user.petOfPlayer.size();
    for(unsigned int i = 0 ; i < x ; i++){
        user.petOfPlayer.pop_back();
    }

    takeCentralWidget();
    setCentralWidget(ui->login);
}
