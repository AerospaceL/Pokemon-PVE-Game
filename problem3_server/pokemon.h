#ifndef POKEMON_H
#define POKEMON_H

#include"pokemonbase.h"

class Charmandar :public pokemonBase
{
public:
    Charmandar(pokemonKind _kind, string _name, int _lv);
    Charmandar(QByteArray &b , int &pos);
    virtual void useSkill(pokemonBase& attacked);
};

class Squirtle :public pokemonBase
{
public:
    Squirtle(pokemonKind _kind, string _name, int _lv);
    Squirtle(QByteArray &b , int &pos);
    virtual void useSkill(pokemonBase& attacked);
};

class Bulbasaur :public pokemonBase
{
public:
    Bulbasaur(pokemonKind _kind, string _name, int _lv);
    Bulbasaur(QByteArray &b , int &pos);
    virtual void useSkill(pokemonBase& attacked);
};

class Pikachu :public pokemonBase
{
public:
    Pikachu(pokemonKind _kind, string _name, int _lv);
    Pikachu(QByteArray &b , int &pos);
    virtual void useSkill(pokemonBase& attacked);
};

#endif // POKEMON_H
