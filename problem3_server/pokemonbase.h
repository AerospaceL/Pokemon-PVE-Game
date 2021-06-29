#ifndef POKEMONBASE_H
#define POKEMONBASE_H

#include"definition.h"
#include<QTextBrowser>

class pokemonBase
{
private:
    pokemonKind kind;
    pokemonGrade grade;
    //string name;
    int lv;
    int xp;
    int xpMax;
    int atk;
    int def;
    int hp;
    int spd;
    int missRate;

    int catk;
    int cdef;
    int chp;
    int cspd;
    int cmissRate;
    int attackTime;

protected:
    QString name;

public:
    pokemonBase(pokemonKind _kind, string _name, int _lv);
    pokemonBase(QByteArray &b, int &pos);

    virtual ~pokemonBase();

    pokemonKind getKind() const { return kind; }
    pokemonGrade getGrade() const { return grade; }
    QString getName() const { return name; }
    int getLv() const { return lv; }
    int getXp() const { return xp; }
    int getXpMax() const { return xpMax; }
    int getAtk() const { return atk; }
    int getDef() const { return def; }
    int getHp() const { return hp; }
    int getSpd() const { return spd; }

    int getChp() const { return chp; }
    int getCatk() const { return catk; }
    int getCdef() const { return cdef; }
    int getCspd() const { return cspd; }
    int getCmissrate() const { return cmissRate; }
    int getAttackTime() const { return attackTime; }

    void changeCatk(int _atk) { catk = _atk; }
    void changeChp(int _hp) { chp = _hp; }
    void changeCdef(int _def) { cdef = _def; }
    void changeCspd(int _spd) { cspd = _spd; }

    void levelUp();
    void Initial();
    void fightStart();
    void figheEnd(int exp);
    //bool fighting(pokemonBase& p);
    void getAttacked(QTextBrowser *p, const pokemonBase& attacker);

    //void print();
    void print(QPainter &p, int x, int y);
    QString pokemonToString();
    void pokemonInfomation(QByteArray &b, int &pos);

    virtual void useSkill(pokemonBase& attacked) = 0;

};

#endif // POKEMONBASE_H
