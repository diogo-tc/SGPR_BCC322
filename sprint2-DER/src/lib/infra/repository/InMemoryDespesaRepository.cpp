#include "InMemoryDespesaRepository.h"

void InMemoryDespesaRepository::clear() {
    despesas.clear();
}

const std::vector<Despesa>& InMemoryDespesaRepository::listar() const {
    return despesas;
}
