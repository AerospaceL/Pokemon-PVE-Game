#ifndef PLAYER_H
#define PLAYER_H

#include"pokemon.h"
#include<QDebug>

class player{
private:
    QString name;
    QString password;
    int winNum;
    int failNum;
    int petNum;
    int highPetNum;
    //vector<pokemonBase *> petOfPlayer;

public:
    vector<pokemonBase *> petOfPlayer;
    player();
    player(QByteArray &b);
    ~player();

    void addPet(pokemonBase *);
    void getPlayerInfo(QByteArray &b , int &pos);
    void getOtherPlayer(QByteArray &b , int &pos);
    QString toQString();

    void win() { winNum++; } ;
    void fail() { failNum++; } ;
    void changePetNum(int num) { petNum = num; } ;
    QString getName() const { return name; } ;
    QString getPassword() const { return password; } ;
    int getWinNum() const { return winNum; } ;
    int getFailNum() const { return failNum; } ;
    int getPetNum() const { return petNum; } ;
    int getHighPetNUm() const { return highPetNum; } ;
    int getPetOfPlayer() const {return petOfPlayer.size();}


};

#endif // PLAYER_H
