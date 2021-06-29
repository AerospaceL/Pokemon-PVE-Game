#include "pokemonbase.h"
#include <iomanip>

pokemonBase::pokemonBase(pokemonKind _kind, string _name, int _lv)
{
    kind = _kind;

    int gradeSign = randNumber(1, 100);
    if (gradeSign == 100)
        grade = GOLDEN;
    else if (gradeSign >= 90)
        grade = PINK;
    else if (gradeSign >= 75)
        grade = PURPLE;
    else if (gradeSign >= 60)
        grade = BLUE;
    else
        grade = GRAY;

    lv = _lv;
    xp = 0;
    xpMax = xpMaxInit;

    atk = lv * atkEachLv + lv * grade * atkGrade;
    def = lv * defEachLv + lv * grade * defGrade;
    hp = lv * hpEachLv + lv * grade * hpGrade;
    spd = 1000 - lv * spdEachLv - lv * grade * spdGrade;
    missRate = 10 + grade;

    switch (kind)
    {
    case ATK:
        atk += lv * atkEachLv;
        break;
    case DEF:
        def += lv * defEachLv;
        break;
    case HP:
        hp += lv * hpEachLv;
        break;
    case SPD:
        spd -= lv * spdEachLv;
        break;
    default:
        break;
    }

}

pokemonBase::pokemonBase(QByteArray &b, int &pos)
{
    get(b, pos);
    kind = pokemonKind(get(b, pos).toInt());
    grade = pokemonGrade(get(b, pos).toInt());
    lv = get(b, pos).toInt();
    xp = get(b, pos).toInt();
    xpMax = xpMaxInit;

    atk = lv * atkEachLv + lv * grade * atkGrade;
    def = lv * defEachLv + lv * grade * defGrade;
    hp = lv * hpEachLv + lv * grade * hpGrade;
    spd = 1000 - lv * spdEachLv - lv * grade * spdGrade;
    missRate = 10 + grade;

    switch (kind)
    {
    case ATK:
        atk += lv * atkEachLv;
        break;
    case DEF:
        def += lv * defEachLv;
        break;
    case HP:
        hp += lv * hpEachLv;
        break;
    case SPD:
        spd -= lv * spdEachLv;
        break;
    default:
        break;
    }
}

pokemonBase::~pokemonBase()
{

}

void pokemonBase::levelUp()
{
    while (xp > xpMax) {
        if (lv < lvUpperLimit) {
            ++lv;
            xp = xp - xpMax;
            xpMax = xpMax * xprate;

            atk = lv * atkEachLv + lv * grade * atkGrade;
            def = lv * defEachLv + lv * grade * defGrade;
            hp = lv * hpEachLv + lv * grade * hpGrade;
            spd = 1000 - lv * spdEachLv - lv * grade * spdGrade;
            missRate = 10 + grade;

            switch (kind)
            {
            case ATK:
                atk += lv * atkEachLv;
                break;
            case DEF:
                def += lv * defEachLv;
                break;
            case HP:
                hp += lv * hpEachLv;
                break;
            case SPD:
                spd -= lv * spdEachLv;
                break;
            default:
                break;
            }

           // cout << "Level Up! " << name << "'s Lv changes to " << lv << " ." << endl;
        }
    }
}

void pokemonBase::Initial()
{
    lv = lvInit;
    xp = 0;
    xpMax = xpMaxInit;

    atk = lv * atkEachLv + lv * grade * atkGrade;
    def = lv * defEachLv + lv * grade * defGrade;
    hp = lv * hpEachLv + lv * grade * hpGrade;
    spd = 1000 - lv * spdEachLv - lv * grade * spdGrade;
    missRate = 10 + grade;

    switch (kind)
    {
    case ATK:
        atk += lv * atkEachLv;
        break;
    case DEF:
        def += lv * defEachLv;
        break;
    case HP:
        hp += lv * hpEachLv;
        break;
    case SPD:
        spd -= lv * spdEachLv;
        break;
    default:
        break;
    }
}

void pokemonBase::fightStart()
{
    chp = hp;
    catk = atk;
    cdef = def;
    cspd = spd;
    cmissRate = missRate;
    attackTime = 0;
}

void pokemonBase::figheEnd(int exp)
{
    xp += exp;
    levelUp();
}

void pokemonBase::getAttacked(QTextBrowser *p, const pokemonBase& attacker)
{
    int miss = randNumber(1, 100);
    if (miss > cmissRate) {
        int damage = attacker.catk - cdef;
        if (chp > damage) {
            chp -= damage;
            p->append(name + " is attacked by " + attacker.name + " , hp - "
                      + QString::number(damage,10)+","+QString::number(getChp(),10)+" hp left!");
            //cout << name << " is attacked by " << attacker.name
                //<< ", - " << damage << " hp!" << endl;
        }
        else {
            chp = 0;
            p->append(name + " is attacked by " + attacker.name + " , hp - " + QString::number(damage,10));
                        p->append(name + " is down !");
            //cout << name << " is attacked by " << attacker.name << ", ";
            //cout << name << " is down ! " << endl;
        }
    }
    else {
        p->append(name + "is attacked by " + attacker.name + " , Miss !");
        //cout << name << " is attacked by " << attacker.name << ", Oh Miss !" << endl;
    }
}

void pokemonBase::print(QPainter &p, int x ,int y)
{
    QFont font("Arial",16,QFont::Bold,true);
    font.setUnderline(false);
    font.setOverline(false);
    font.setCapitalization(QFont::SmallCaps);
    font.setLetterSpacing(QFont::AbsoluteSpacing,3);
    p.setFont(font);

    int length = 200;
    int width = 50;
    QString temp;

    //print name with grade
    temp.clear();
    temp += "名称:";
    temp += name;
    QRectF ff1(x,y,length,width);
    p.drawRect(ff1);

    switch(grade){
    case GRAY:
        p.setPen(QColor(Qt::gray));
        break;
    case BLUE:
        p.setPen(QColor(Qt::blue));
        break;
    case PURPLE:
        p.setPen(QColor(Qt::magenta));
        break;
    case PINK:
        p.setPen(QColor(Qt::red));
        break;
    case GOLDEN:
        p.setPen(QColor(Qt::yellow));
        break;
    default:
        break;
    }
    p.drawText(ff1,Qt::AlignCenter,temp);
    p.setPen(QColor(Qt::black));

    //print kind
    temp.clear();
    temp += "种类:";
    QRectF ff2(x,y + width,length,width);
    p.drawRect(ff2);
    switch(kind){
    case ATK:
        temp += "ATK";
        break;
        temp += "DEF";
        break;
    case HP:
        temp += "HP";
        break;
    case SPD:
        temp += "SPD";
        break;
    default:
        temp += "error";
        break;
    }
    p.drawText(ff2,Qt::AlignCenter,temp);


    //print lv
    temp.clear();
    temp += "等级:";
    temp += QString::number(lv,10);
    QRectF ff3(x,y + width * 2,length,width);
    p.drawRect(ff3);
    p.drawText(ff3,Qt::AlignCenter,temp);

    //print xp / xpMax
    temp.clear();
    temp += "经验:";
    temp += QString::number(xp,10);
    temp += "/";
    temp += QString::number(xpMax,10);
    QRectF ff4(x,y + width * 3,length,width);
    p.drawRect(ff4);
    p.drawText(ff4,Qt::AlignCenter,temp);

    //print hp
    temp.clear();
    temp += "hp:";
    temp += QString::number(hp,10);
    QRectF ff5(x,y + width * 4,length,width);
    p.drawRect(ff5);
    p.drawText(ff5,Qt::AlignCenter,temp);

    //print atk
    temp.clear();
    temp += "攻击力:";
    temp += QString::number(atk,10);
    QRectF ff6(x,y + width * 5,length,width);
    p.drawRect(ff6);
    p.drawText(ff6,Qt::AlignCenter,temp);

    //print def
    temp.clear();
    temp += "防御力:";
    temp += QString::number(def,10);
    QRectF ff7(x,y + width * 6,length,width);
    p.drawRect(ff7);
    p.drawText(ff7,Qt::AlignCenter,temp);

    //print atk interval
    temp.clear();
    temp += "攻击间隔:";
    temp += QString::number(spd,10);
    QRectF ff8(x,y + width * 7,length,width);
    p.drawRect(ff8);
    p.drawText(ff8,Qt::AlignCenter,temp);
}

QString pokemonBase::pokemonToString()
{
    QString temp;
    temp += name;
    temp += ' ';
    temp += QString::number(kind,10);
    temp += ' ';
    temp += QString::number(grade,10);
    temp += ' ';
    temp += QString::number(lv,10);
    temp += ' ';
    temp += QString::number(xp,10);
    return temp;
}

void pokemonBase::pokemonInfomation(QByteArray &b, int &pos)
{
    name = get(b, pos);
    kind = pokemonKind(get(b, pos).toInt());
    grade = pokemonGrade(get(b, pos).toInt());
    lv = get(b, pos).toInt();
    xp = get(b, pos).toInt();
    xpMax = xpMaxInit;

    atk = lv * atkEachLv + lv * grade * atkGrade;
    def = lv * defEachLv + lv * grade * defGrade;
    hp = lv * hpEachLv + lv * grade * hpGrade;
    spd = 1000 - lv * spdEachLv - lv * grade * spdGrade;
    missRate = 10 + grade;

    switch (kind)
    {
    case ATK:
        atk += lv * atkEachLv;
        break;
    case DEF:
        def += lv * defEachLv;
        break;
    case HP:
        hp += lv * hpEachLv;
        break;
    case SPD:
        spd -= lv * spdEachLv;
        break;
    default:
        break;
    }
}
