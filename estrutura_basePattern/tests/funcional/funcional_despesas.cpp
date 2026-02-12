#include <cassert>

#include "funcional_despesas.h"

void testeRegistrarDespesaValida() {
    auto servico = infra::factory::createServicoDespesas();

    bool sucesso = servico.registrarDespesa("Acucar", 5.00, "05/02/2026");

    assert(sucesso);
    assert(servico.listarDespesas().size() == 1);

    const Despesa& d = servico.listarDespesas()[0];
    assert(d.getDescricao() == "Acucar");
    assert(d.getValor() == 5.00);
    assert(d.getData() == "05/02/2026");
}

void testeRegistrarDespesaSemValor() {
    auto servico = infra::factory::createServicoDespesas();

    bool sucesso = servico.registrarDespesa("Acucar", 0, "05/02/2026");

    assert(!sucesso);
    assert(servico.listarDespesas().empty());
}
