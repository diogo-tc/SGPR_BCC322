#include <cassert>
#include <vector>

#include "funcional_rateio.h"

void testeRateioComMoradores() {
    auto despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    std::vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    auto rateio = infra::factory::createServicoRateio();
    auto resultado = rateio.calcularRateio(
        despesas.listarDespesas(),
        moradores
    );

    assert(resultado.size() == 2);

    for (const auto& r : resultado) {
        assert(r.getValor() == 600.0);
    }
}

void testeRateioSemMoradores() {
    auto despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Luz", 300.00, "02/02/2026");

    std::vector<Usuario> moradores;
    auto rateio = infra::factory::createServicoRateio();

    bool excecao = false;

    try {
        rateio.calcularRateio(despesas.listarDespesas(), moradores);
    } catch (...) {
        excecao = true;
    }

    assert(excecao);
}
