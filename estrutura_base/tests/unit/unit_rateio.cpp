#include <cassert>
#include <vector>

#include "../../src/lib/services/ServicoDespesas.h"
#include "../../src/lib/services/ServicoRateio.h"
#include "../../src/lib/domain/Usuario.h"

void testeRateioComMoradores() {
    ServicoDespesas despesas;
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    std::vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    ServicoRateio rateio;

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
    ServicoDespesas despesas;
    despesas.registrarDespesa("Luz", 300.00, "02/02/2026");

    std::vector<Usuario> moradores;
    ServicoRateio rateio;

    bool lancou = false;

    try {
        rateio.calcularRateio(despesas.listarDespesas(), moradores);
    } catch (...) {
        lancou = true;
    }

    assert(lancou == true);
}
