#include "ServicoDespesas.h"

bool ServicoDespesas::registrarDespesa(const std::string& descricao,
                                       double valor,
                                       const std::string& data) {
    if (descricao.empty() || data.empty() || valor <= 0) {
        return false;
    }

    despesas.emplace_back(descricao, valor, data);
    return true;
}

const std::vector<Despesa>& ServicoDespesas::listarDespesas() const {
    return despesas;
}
