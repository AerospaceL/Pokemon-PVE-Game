#include "player.h"

//构造函数
player::player()
{}

player::player(QByteArray &b)
{
    int pos = 0;
    get(b, pos);
    name = get(b, pos);
    password = get(b, pos);
    winNum = get(b, pos).toInt();
    failNum = get(b, pos).toInt();
    petNum = get(b, pos).toInt();
    highPetNum = get(b, pos).toInt();
    while(pos < b.size()){
        int n = pos;
        QString temp;
        temp.clear();
        temp += get(b,n);
        pokemonBase *p;
        if(temp == pokemonName[0]){
            p = new Charmandar(b,pos);
        }
        else if(temp == pokemonName[1]){
            p = new Squirtle(b,pos);
        }
        else if(temp == pokemonName[2]){
            p = new Bulbasaur(b,pos);
        }
        else if(temp == pokemonName[3]){
            p = new Pikachu(b,pos);
        }
        petOfPlayer.push_back(p);
    }

}


player::~player()
{
    for(unsigned int i = 0 ; i < petOfPlayer.size() ; i++){
        delete petOfPlayer[i];
    }
}


//用户获得新的小精灵的方法
void player::addPet(pokemonBase *p)
{
    petOfPlayer.push_back(p);
}


//从字符串中提取出用户信息的方法
void player::getPlayerInfo(QByteArray &b, int &pos)
{
    name = get(b,pos);
    password = get(b,pos);
    winNum = get(b,pos).toInt();
    failNum = get(b,pos).toInt();
    petNum = get(b,pos).toInt();
    highPetNum = get(b,pos).toInt();

    pokemonBase *p;
    while(b[pos] != '#'){
        int n = pos;
        get(b,n);    //get name
        //kind
        switch(get(b,n).toInt()){
        case 0:
            p = new Charmandar(ATK,"smallFireDragon",lvInit);
            break;
        case 1:
            p = new Squirtle(DEF,"bigStone",lvInit);
            break;
        case 2:
            p = new Bulbasaur(HP,"oldTree",lvInit);
            break;
        case 3:
            p = new Pikachu(SPD,"pikachu",lvInit);
            break;
        default:
            break;
        }
        p->pokemonInfomation(b, pos);
        petOfPlayer.push_back(p);
    }
}


//从字符串中提取其他在线用户信息方法
void player::getOtherPlayer(QByteArray &b , int &pos)
{
    name = get(b,pos);

    winNum = get(b,pos).toInt();
    failNum = get(b,pos).toInt();
    petNum = get(b,pos).toInt();
    highPetNum = get(b,pos).toInt();

    //QString temp;
    pokemonBase *p;
    while(b[pos] != '#'){
        int n = pos;
        get(b,n);    //get name
        //kind
        switch(get(b,n).toInt()){
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
        p->pokemonInfomation(b,pos);
        petOfPlayer.push_back(p);
    }
}

QString player::getWinRate()
{
    int winRate = 0;
    QString temp;
    if(winNum == 0 && failNum == 0){
        temp = "0%";
    }
    else if(winNum != 0 && failNum == 0){
        temp = "100%";
    }
    else{
        winRate = (winNum * 100) / (winNum + failNum);
        temp = QString::number(winRate,10) + "%";
    }
    return temp;
}

//将用户信息变成字符串传送的方法
QString player::toQString()
{
    QString temp;
    temp.clear();

    temp += name;
    temp += ' ';
    temp += QString::number(winNum,10);
    temp += ' ';
    temp += QString::number(failNum,10);
    temp += ' ';
    temp += QString::number(petNum,10);
    temp += ' ';
    temp += QString::number(highPetNum,10);
    temp += ' ';
    for(unsigned int i = 0 ; i < petOfPlayer.size() ; ++i){
        temp += petOfPlayer[i]->pokemonToString();
        //qDebug() << temp;
        temp += ' ';
    }
    temp += "#";
    return temp;
}
