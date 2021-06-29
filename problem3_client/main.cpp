#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <windows.h>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

QString get(const QByteArray &b , int &pos)
{
    QString str;
    str.clear();
    for( ; pos < b.size() ; pos++){
        if(b[pos] == ' '){
            ++pos;
            return str;
        }
        else{
            str += b[pos];
        }
    }
    return str;
}

int randNumber(int left, int right)
{
    return ((rand() % (right - left + 1)) + left);
}
