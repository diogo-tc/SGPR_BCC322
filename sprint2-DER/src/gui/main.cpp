#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "loginwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sgpr.db");

    if(!db.open()) {
        qDebug() << "Erro ao abrir banco";
        return -1;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS usuarios ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "nome TEXT NOT NULL,"
               "senha TEXT NOT NULL)");

    LoginWindow w;
    w.show();

    return a.exec();
}