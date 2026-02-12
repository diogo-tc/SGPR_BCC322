#include "funcional.h"

//testes de rateio
void testeRateioComMoradores() {
    auto despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    vector<Usuario> moradores = {
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

    vector<Usuario> moradores;
    auto rateio = infra::factory::createServicoRateio();

    bool excecao = false;

    try {
        rateio.calcularRateio(despesas.listarDespesas(), moradores);
    } catch (...) {
        excecao = true;
    }

    assert(excecao);
}

//testes de extrato

void testeExtratoComSaldoInicial() {
    auto despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    auto rateioService = infra::factory::createServicoRateio();
    auto rateios = rateioService.calcularRateio(
        despesas.listarDespesas(),
        moradores
    );

    map<string, double> saldos;
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
    vector<Rateio> rateios;
    map<string, double> saldos;

    auto extratoService = infra::factory::createServicoExtrato();

    bool excecao = false;

    try {
        extratoService.gerarExtrato(rateios, saldos);
    } catch (...) {
        excecao = true;
    }

    assert(excecao);
}

//testes de despesas 

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
