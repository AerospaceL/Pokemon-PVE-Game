#ifndef DEFINITION_H
#define DEFINITION_H

#include<string>
#include<time.h>
#include<vector>
#include<stdlib.h>
#include<QString>
#include<QPainter>
#include<iostream>
using namespace std;

enum pokemonKind
{
    ATK,	// High attack
    DEF,	// High defence
    HP,		// High HP
    SPD		// Low attack interval
};

enum pokemonGrade
{
    GRAY,	// Normal kind
    BLUE,	// Rare
    PURPLE,	// Epic
    PINK,	// Artifact
    GOLDEN	// WOW! Golden Legend!
};

const int lvInit = 1;
const int lvUpperLimit = 15;

const int atkEachLv = 45;
const int defEachLv = 15;
const int hpEachLv = 200;
const int spdEachLv = 40;
const int xprate = 1;
const int xpMaxInit = 100;
const int performRate = 20;
const int atkGrade =10;
const int defGrade = 4;
const int hpGrade = 40;
const int spdGrade = 10;

const QString pokemonName[4] = {
    "Charmandar",	// 小火龙   --> 攻击型
    "Squirtle",		// 杰尼龟   --> 防御型
    "Bulbasaur",	// 妙蛙种子 --> 肉盾型
    "Pikachu"		// 皮卡丘   --> 敏捷型
};

const QString loginFailed = "loginisfailed";
const QString loginSucceeded = "loginissuccessful";
const QString userNameIsIn = "uesrnameisin";
const QString registSucceeded = "registissuccessful";

int randNumber(int left, int right);
QString get(const QByteArray &b , int &pos);


#endif // DEFINITION_H
