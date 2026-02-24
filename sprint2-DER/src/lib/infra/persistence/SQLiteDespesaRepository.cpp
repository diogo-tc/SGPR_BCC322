#include "SQLiteDespesaRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QUuid>

SQLiteDespesaRepository::SQLiteDespesaRepository() {

    // Gera nome único para evitar conflito de conexão
    connectionName = QUuid::createUuid().toString();

    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName("sgpr.db");

    if (!db.open()) {
        qDebug() << "Erro ao abrir banco:" << db.lastError().text();
    }

    inicializarBanco();
}

SQLiteDespesaRepository::~SQLiteDespesaRepository() {

    if (db.isOpen()) {
        db.close();
    }

    // Remove referência antes de remover conexão (exigência do Qt)
    db = QSqlDatabase();

    QSqlDatabase::removeDatabase(connectionName);
}

void SQLiteDespesaRepository::inicializarBanco() {

    QSqlQuery query(db);

    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS despesas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "descricao TEXT,"
        "valor REAL,"
        "data TEXT)"
    )) {
        qDebug() << "Erro ao criar tabela:" << query.lastError().text();
    }
}

void SQLiteDespesaRepository::adicionar(const Despesa& d) {

    QSqlQuery query(db);

    query.prepare(
        "INSERT INTO despesas (descricao, valor, data) "
        "VALUES (?, ?, ?)"
    );

    query.addBindValue(QString::fromStdString(d.getDescricao()));
    query.addBindValue(d.getValor());
    query.addBindValue(QString::fromStdString(d.getData()));

    if (!query.exec()) {
        qDebug() << "Erro ao inserir despesa:" << query.lastError().text();
    }
}

const std::vector<Despesa>& SQLiteDespesaRepository::listar() const {

    cache.clear();

    QSqlQuery query(db);

    if (!query.exec("SELECT descricao, valor, data FROM despesas")) {
        qDebug() << "Erro ao listar despesas:" << query.lastError().text();
        return cache;
    }

    while (query.next()) {

        std::string descricao = query.value(0).toString().toStdString();
        double valor = query.value(1).toDouble();
        std::string data = query.value(2).toString().toStdString();

        cache.emplace_back(descricao, valor, data);
    }

    return cache;
    }

void SQLiteDespesaRepository::clear() {
        QSqlQuery query;
        query.exec("DELETE FROM despesas");
}