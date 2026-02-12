#include <cassert>
#include <vector>
#include <map>

#include "../../src/lib/services/ServicoDespesas.h"
#include "../../src/lib/services/ServicoRateio.h"
#include "../../src/lib/services/ServicoExtrato.h"
#include "../../src/lib/domain/Usuario.h"
#include "../../src/lib/domain/Rateio.h"
#include "../../src/lib/infra/factory/Factory.h"

void testeExtratoComSaldoInicial() {
    auto despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    std::vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    auto rateioService = infra::factory::createServicoRateio();
    auto rateios = rateioService.calcularRateio(
        despesas.listarDespesas(),
        moradores
    );

    std::map<std::string, double> saldos;
    saldos["Ana"] = 200.0;
    saldos["Bruno"] = 0.0;

    auto extratoService = infra::factory::createServicoExtrato();
    auto extratos = extratoService.gerarExtrato(rateios, saldos);

    assert(extratos.size() == 2);

    for (const auto& e : extratos) {
        if (e.getUsuario() == "Ana") {
            assert(e.getSaldoInicial() == 200.0);
            assert(e.getValorRateio() == 600.0);
            assert(e.getSaldoFinal() == -400.0);
        }
    }
}

void testeExtratoSemRateio() {
    std::vector<Rateio> rateios;
    std::map<std::string, double> saldos;

    auto extratoService = infra::factory::createServicoExtrato();

    bool excecao = false;

    try {
        extratoService.gerarExtrato(rateios, saldos);
    } catch (...) {
        excecao = true;
    }

    assert(excecao);
}