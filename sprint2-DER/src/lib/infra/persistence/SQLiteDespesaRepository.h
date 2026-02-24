#ifndef SQLITE_DESPESA_REPOSITORY_H
#define SQLITE_DESPESA_REPOSITORY_H

#include "../repository/IDespesaRepository.h"
#include <QSqlDatabase>
#include <QString>
#include <vector>

class SQLiteDespesaRepository : public IDespesaRepository {
public:
    SQLiteDespesaRepository();
    ~SQLiteDespesaRepository();

    void adicionar(const Despesa& d) override;
    const std::vector<Despesa>& listar() const override;
    void clear() override;

private:
    void inicializarBanco();

    mutable std::vector<Despesa> cache;
    QSqlDatabase db;
    QString connectionName;   
};

#endif