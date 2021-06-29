#include "database.h"
#include <QDebug>

Database::Database()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("Lbase.db");
        database.setUserName("12345");
        database.setPassword("211210");
    }

    if (!database.open())
    {
        qDebug() << "Failed to connect the database.";
    }
    else
    {
        query = new QSqlQuery(database);
        QString createSql = "CREATE TABLE player (name TEXT primary key, password TEXT, winNum INT, failNum INT, petNum INT, highPetNum INT, pet TEXT);";

        if(query->exec(createSql)){
            qDebug() << "Failed to create table player.";
        }
        else{
            qDebug() << "Table player created.";
        }

    }
}

Database::~Database()
{
    database.close();
}
