#ifndef INMEMORY_DESPESA_REPOSITORY_H
#define INMEMORY_DESPESA_REPOSITORY_H

#include "IDespesaRepository.h"
#include <vector>

class InMemoryDespesaRepository : public IDespesaRepository {
private:
    std::vector<Despesa> despesas;

public:
    void adicionar(const Despesa& d) override;
    const std::vector<Despesa>& listar() const override;
};

#endif
