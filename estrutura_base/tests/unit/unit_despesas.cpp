#include <cassert>
#include "../../src/lib/services/ServicoDespesas.h"
#include "../../src/lib/domain/Despesa.h"

void testeRegistrarDespesaValida() {
    ServicoDespesas servico;

    bool sucesso = servico.registrarDespesa("Acucar", 5.00, "05/02/2026");

    assert(sucesso == true);
    assert(servico.listarDespesas().size() == 1);

    const Despesa& d = servico.listarDespesas()[0];
    assert(d.getDescricao() == "Acucar");
    assert(d.getValor() == 5.00);
    assert(d.getData() == "05/02/2026");
}

void testeRegistrarDespesaSemValor() {
    ServicoDespesas servico;

    bool sucesso = servico.registrarDespesa("Acucar", 0, "05/02/2026");

    assert(sucesso == false);
    assert(servico.listarDespesas().empty());
}
