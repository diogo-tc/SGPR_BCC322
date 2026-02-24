#include "ServicoDespesas.h"
#include "../infra/factory/Factory.h"

ServicoDespesas::ServicoDespesas()
    : repo(infra::factory::createSQLiteDespesaRepository()) {}

ServicoDespesas::ServicoDespesas(std::unique_ptr<IDespesaRepository> repository)
    : repo(std::move(repository)) {}

bool ServicoDespesas::registrarDespesa(const std::string& descricao,
                                       double valor,
                                       const std::string& data) {
    if (descricao.empty() || data.empty() || valor <= 0) {
        return false;
    }

    Despesa d(descricao, valor, data);
    repo->adicionar(d);
    return true;
}

const std::vector<Despesa>& ServicoDespesas::listarDespesas() const {
    return repo->listar();
}

// ===== NOVO MÉTODO =====
bool ServicoDespesas::apagarTodas() {
    repo->clear();   // chama o clear() do repositório
    return true;
}