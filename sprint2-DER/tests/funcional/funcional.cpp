#include "funcional.h"
#include <cassert>

// =================================================
// TESTES DE RATEIO
// =================================================

void testeRateioComMoradores() {

    auto despesasService = infra::factory::createServicoDespesas();

    size_t tamanhoAntes = despesasService.listarDespesas().size();

    despesasService.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    auto listaAtual = despesasService.listarDespesas();
    assert(listaAtual.size() == tamanhoAntes + 1);

    vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    auto rateio = infra::factory::createServicoRateio();
    auto resultado = rateio.calcularRateio(listaAtual, moradores);

    assert(resultado.size() == 2);

    // calcula valor esperado dinamicamente
    double soma = 0.0;
    for (const auto& d : listaAtual) {
        soma += d.getValor();
    }

    double valorEsperado = soma / moradores.size();

    for (const auto& r : resultado) {
        assert(r.getValor() == valorEsperado);
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

// =================================================
// TESTES DE EXTRATO
// =================================================

void testeExtratoComSaldoInicial() {

    auto despesasService = infra::factory::createServicoDespesas();

    size_t tamanhoAntes = despesasService.listarDespesas().size();

    despesasService.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    auto listaAtual = despesasService.listarDespesas();
    assert(listaAtual.size() == tamanhoAntes + 1);

    vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    auto rateioService = infra::factory::createServicoRateio();
    auto rateios = rateioService.calcularRateio(listaAtual, moradores);

    // calcula soma total dinamicamente
    double soma = 0.0;
    for (const auto& d : listaAtual) {
        soma += d.getValor();
    }

    double valorEsperado = soma / moradores.size();

    map<string, double> saldos;
    saldos["Ana"] = 200.0;
    saldos["Bruno"] = 0.0;

    auto extratoService = infra::factory::createServicoExtrato();
    auto extratos = extratoService.gerarExtrato(rateios, saldos);

    assert(extratos.size() == 2);

    for (const auto& e : extratos) {
        if (e.getUsuario() == "Ana") {
            assert(e.getSaldoInicial() == 200.0);
            assert(e.getValorRateio() == valorEsperado);
            assert(e.getSaldoFinal() == 200.0 - valorEsperado);
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

// =================================================
// TESTES DE DESPESAS
// =================================================

void testeRegistrarDespesaValida() {

    auto servico = infra::factory::createServicoDespesas();

    size_t tamanhoAntes = servico.listarDespesas().size();

    bool sucesso = servico.registrarDespesa("Acucar", 5.00, "05/02/2026");

    assert(sucesso);

    auto lista = servico.listarDespesas();
    assert(lista.size() == tamanhoAntes + 1);

    const Despesa& d = lista.back();
    assert(d.getDescricao() == "Acucar");
    assert(d.getValor() == 5.00);
    assert(d.getData() == "05/02/2026");
}

void testeRegistrarDespesaSemValor() {

    auto servico = infra::factory::createServicoDespesas();

    size_t tamanhoAntes = servico.listarDespesas().size();

    bool sucesso = servico.registrarDespesa("Acucar", 0, "05/02/2026");

    assert(!sucesso);

    auto lista = servico.listarDespesas();
    assert(lista.size() == tamanhoAntes);
}