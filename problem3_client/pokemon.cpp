#include "pokemon.h"


Charmandar::Charmandar(pokemonKind _kind, string _name, int _lv)
    :pokemonBase(_kind, _name, _lv)
{
    name = pokemonName[0];
}

Charmandar::Charmandar(QByteArray &b , int &pos)
    :pokemonBase(b,pos)
{
    name = pokemonName[0];
}

void Charmandar::useSkill(QTextBrowser *p , pokemonBase& attacked)
{
    changeCatk(getCatk() + atkEachLv);
    p->append("Charmander uses skill [Dragon Wrath] , atk improves " +
              QString::number(atkEachLv,10) + "," + QString::number(getCatk(),10) + " atk now!");

}

Squirtle::Squirtle(pokemonKind _kind, string _name, int _lv)
    :pokemonBase(_kind, _name, _lv)
{
    name = pokemonName[1];
}

Squirtle::Squirtle(QByteArray &b , int &pos)
    :pokemonBase(b,pos)
{
    name = pokemonName[1];
}

void Squirtle::useSkill(QTextBrowser *p , pokemonBase& attacked)
{
    changeCdef(getCdef() + defEachLv);
    p->append("Squirtle uses skill [Shell Shrinking] , def improves " +
              QString::number(defEachLv,10) + "," + QString::number(getCdef(),10) + " def now!");
}

Bulbasaur::Bulbasaur(pokemonKind _kind, string _name, int _lv)
    :pokemonBase(_kind, _name, _lv)
{
    name = pokemonName[2];
}

Bulbasaur::Bulbasaur(QByteArray &b , int &pos)
    :pokemonBase(b,pos)
{
    name = pokemonName[2];
}

void Bulbasaur::useSkill(QTextBrowser *p , pokemonBase& attacked)
{
    if (getChp() >= (getHp() - 50)) {
        changeChp(getHp());
    }
    else {
        changeChp(getChp() + 50);
    }
    p->append("Bulbasaur uses skill [Leech Seed] , HP has recovered ! " +
              QString::number(getCdef(),10) + " def now!");

}

Pikachu::Pikachu(pokemonKind _kind, string _name, int _lv)
    :pokemonBase(_kind, _name, _lv)
{
    name = pokemonName[3];
}

Pikachu::Pikachu(QByteArray &b , int &pos)
    :pokemonBase(b,pos)
{
    name = pokemonName[3];
}

void Pikachu::useSkill(QTextBrowser *p , pokemonBase& attacked)
{
    p->append("Pikachu uses [Quick Attack] , causes " + QString::number(getAtk() * 2,10) + " damage");
    if (getCatk() * 2 <= attacked.getChp()) {
        attacked.changeChp(attacked.getChp() - getCatk() * 2);
    }
    else {
        attacked.changeChp(0);
        p->append(attacked.getName() + " is down !");
    }
}
