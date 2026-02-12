#include <iostream>
#include <vector>
#include <map>

#include "services/ServicoDespesas.h"
#include "services/ServicoRateio.h"
#include "services/ServicoExtrato.h"
#include "infra/factory/Factory.h"

#include "domain/Usuario.h"
#include "domain/Despesa.h"
#include "domain/Rateio.h"
#include "domain/Extrato.h"

/* =====================================================
   TESTES DO SERVICO DE DESPESAS
   ===================================================== */

void testeRegistrarDespesaValida() {
    std::cout << "Cenario: Registrar despesa com dados validos\n";
    ServicoDespesas servico = infra::factory::createServicoDespesas();
    bool sucesso = servico.registrarDespesa("Acucar", 5.00, "05/02/2026");

    if (sucesso && servico.listarDespesas().size() == 1) {
        const Despesa& d = servico.listarDespesas()[0];
        std::cout << "✔ Despesa registrada: "
                  << d.getDescricao()
                  << " | R$ " << d.getValor()
                  << " | " << d.getData() << "\n";
    } else {
        std::cout << "✘ Falha ao registrar despesa valida\n";
    }

    std::cout << "---------------------------------\n";
}

void testeRegistrarDespesaSemValor() {
    std::cout << "Cenario: Tentar registrar despesa sem valor\n";
    ServicoDespesas servico = infra::factory::createServicoDespesas();
    bool sucesso = servico.registrarDespesa("Acucar", 0, "05/02/2026");

    if (!sucesso && servico.listarDespesas().empty()) {
        std::cout << "✔ Despesa nao registrada, dados invalidos\n";
    } else {
        std::cout << "✘ Erro: despesa invalida foi registrada\n";
    }

    std::cout << "---------------------------------\n";
}

/* =====================================================
   TESTES DO SERVICO DE RATEIO
   ===================================================== */

void testeRateioComMoradores() {
    std::cout << "Cenario: Rateio de despesa entre dois moradores\n";
    ServicoDespesas despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    std::vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    ServicoRateio rateio = infra::factory::createServicoRateio();
    auto resultado = rateio.calcularRateio(
        despesas.listarDespesas(),
        moradores
    );

    if (resultado.size() == 2) {
        bool correto = true;

        for (const auto& r : resultado) {
            std::cout << r.getUsuario()
                      << " deve pagar R$ "
                      << r.getValor() << "\n";

            if (r.getValor() != 600.0) {
                correto = false;
            }
        }

        if (correto) {
            std::cout << "✔ Rateio correto: R$ 600 para cada morador\n";
        } else {
            std::cout << "✘ Erro no valor do rateio\n";
        }
    }

    std::cout << "---------------------------------\n";
}

void testeRateioSemMoradores() {
    std::cout << "Cenario: Tentar realizar rateio sem moradores\n";
    ServicoDespesas despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Luz", 300.00, "02/02/2026");

    std::vector<Usuario> moradores;
    ServicoRateio rateio = infra::factory::createServicoRateio();

    try {
        rateio.calcularRateio(despesas.listarDespesas(), moradores);
        std::cout << "✘ Erro: rateio invalido foi realizado\n";
    } catch (...) {
        std::cout << "✔ Rateio corretamente bloqueado\n";
    }

    std::cout << "---------------------------------\n";
}

/* =====================================================
   TESTES DO SERVICO DE EXTRATO (COM SALDO EM CAIXA)
   ===================================================== */

void testeExtratoComSaldoInicial() {
    std::cout << "Cenario: Gerar extrato considerando saldo inicial\n";
    ServicoDespesas despesas = infra::factory::createServicoDespesas();
    despesas.registrarDespesa("Aluguel", 1200.00, "01/02/2026");

    std::vector<Usuario> moradores = {
        Usuario("Ana"),
        Usuario("Bruno")
    };

    ServicoRateio rateioService = infra::factory::createServicoRateio();
    auto rateios = rateioService.calcularRateio(
        despesas.listarDespesas(),
        moradores
    );

    std::map<std::string, double> saldosIniciais;
    saldosIniciais["Ana"] = 200.0;   // Ana já contribuiu antes
    saldosIniciais["Bruno"] = 0.0;   // Bruno não contribuiu

    ServicoExtrato extratoService = infra::factory::createServicoExtrato();
    auto extratos = extratoService.gerarExtrato(rateios, saldosIniciais);

    if (extratos.size() == 2) {
        for (const auto& e : extratos) {
            std::cout << e.getUsuario() << "\n";
            std::cout << "Saldo inicial: R$ " << e.getSaldoInicial() << "\n";
            std::cout << "Rateio: R$ " << e.getValorRateio() << "\n";
            std::cout << "Saldo final: R$ " << e.getSaldoFinal() << "\n";
            std::cout << "-----------------------------\n";
        }
        std::cout << "✔ Extrato gerado corretamente com saldo\n";
    } else {
        std::cout << "✘ Erro na geracao do extrato\n";
    }

    std::cout << "---------------------------------\n";
}

void testeExtratoSemRateio() {
    std::cout << "Cenario: Tentar gerar extrato sem rateio\n";

    std::vector<Rateio> rateios;
    std::map<std::string, double> saldos;

    ServicoExtrato extratoService = infra::factory::createServicoExtrato();

    try {
        extratoService.gerarExtrato(rateios, saldos);
        std::cout << "✘ Erro: extrato gerado sem rateio\n";
    } catch (...) {
        std::cout << "✔ Extrato corretamente bloqueado\n";
    }

    std::cout << "---------------------------------\n";
}

/* =====================================================
   MAIN
   ===================================================== */

int main() {
    testeRegistrarDespesaValida();
    testeRegistrarDespesaSemValor();

    testeRateioComMoradores();
    testeRateioSemMoradores();

    testeExtratoComSaldoInicial();
    testeExtratoSemRateio();

    return 0;
}
