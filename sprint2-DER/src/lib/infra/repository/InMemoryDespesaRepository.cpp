#include "InMemoryDespesaRepository.h"

void InMemoryDespesaRepository::adicionar(const Despesa& d) {
    despesas.push_back(d);
}

const std::vector<Despesa>& InMemoryDespesaRepository::listar() const {
    return despesas;
}
