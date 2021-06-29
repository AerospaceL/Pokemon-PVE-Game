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

void Charmandar::useSkill(pokemonBase& attacked)
{
    changeCatk(getCatk() + atkEachLv);
    //cout << name << " uses [ATK improve], atk + " << atkEachLv << " !" << endl;
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

void Squirtle::useSkill(pokemonBase& attacked)
{
    changeCdef(getCdef() + defEachLv);
    //cout << name << " uses [DEF improve], def + " << defEachLv << " ! " << endl;
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

void Bulbasaur::useSkill(pokemonBase& attacked)
{
    changeChp(getHp());
    //cout << name << " has recovered all HP! HP is full now! " << endl;
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

void Pikachu::useSkill(pokemonBase& attacked)
{
    cout << "pikachu uses [LIGHTEN], cause " << getCatk() * 2 << " damage!" << endl;
    if (getCatk() * 2 <= attacked.getChp()) {
        attacked.changeChp(attacked.getChp() - getCatk() * 2);
        //cout << attacked.getName() << " gets " << getCatk() * 2 << " damage!" << endl;
    }
    else {
        attacked.changeChp(0);
        //cout << attacked.getName() << " is down !" << endl;
    }
}
