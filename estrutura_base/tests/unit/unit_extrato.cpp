#include <cassert>
#include <vector>
#include <map>

#include "../../src/lib/services/ServicoDespesas.h"
#include "../../src/lib/services/ServicoRateio.h"
#include "../../src/lib/services/ServicoExtrato.h"
#include "../../src/lib/domain/Usuario.h"
#include "../../src/lib/domain/Rateio.h"

void testeExtratoComSaldoInicial() {
    ServicoDespesas despesas;
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    std::vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    ServicoRateio rateioService;
    auto rateios = rateioService.calcularRateio(
        despesas.listarDespesas(),
        moradores
    );

    std::map<std::string, double> saldos;
    saldos["Ana"] = 200.0;
    saldos["Bruno"] = 0.0;

    ServicoExtrato extratoService;
    auto extratos = extratoService.gerarExtrato(rateios, saldos);

    assert(extratos.size() == 2);
}

void testeExtratoSemRateio() {
    std::vector<Rateio> rateios;
    std::map<std::string, double> saldos;

    ServicoExtrato extratoService;

    bool lancou = false;

    try {
        extratoService.gerarExtrato(rateios, saldos);
    } catch (...) {
        lancou = true;
    }

    assert(lancou == true);
}
