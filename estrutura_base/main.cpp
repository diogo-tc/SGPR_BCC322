#include <iostream>
#include <vector>

#include "services/ServicoDespesas.h"
#include "services/ServicoRateio.h"
#include "domain/Usuario.h"

/* ===============================
   TESTES DE DESPESA
   =============================== */

void testeRegistrarDespesaValida() {
    std::cout << "Cenário: Registrar despesa com dados válidos\n";

    ServicoDespesas servico;
    bool sucesso = servico.registrarDespesa("açúcar", 5.00, "05/02/2026");

    if (sucesso && servico.listarDespesas().size() == 1) {
        const Despesa& d = servico.listarDespesas()[0];
        std::cout << "✔ Despesa registrada: "
                  << d.getDescricao()
                  << " | R$ " << d.getValor()
                  << " | " << d.getData() << "\n";
    } else {
        std::cout << "✘ Falha ao registrar despesa válida\n";
    }

    std::cout << "---------------------------------\n";
}

void testeRegistrarDespesaSemValor() {
    std::cout << "Cenário: Tentar registrar despesa sem valor\n";

    ServicoDespesas servico;
    bool sucesso = servico.registrarDespesa("açúcar", 0, "05/02/2026");

    if (!sucesso && servico.listarDespesas().empty()) {
        std::cout << "✔ despesa não registrada, dados incompletos\n";
    } else {
        std::cout << "✘ Erro: despesa inválida foi registrada\n";
    }

    std::cout << "---------------------------------\n";
}

/* ===============================
   TESTES DE RATEIO
   =============================== */

void testeRateioComMoradores() {
    std::cout << "Cenário: Rateio de despesa entre dois moradores\n";

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

    if (resultado.size() == 2) {
        std::cout << "Despesa total: R$ 1200\n";
        std::cout << "Numero de moradores: 2\n";

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
    } else {
        std::cout << "✘ Erro: quantidade incorreta de rateios\n";
    }

    std::cout << "---------------------------------\n";
}

void testeRateioSemMoradores() {
    std::cout << "Cenário: Tentar rateio sem moradores\n";

    ServicoDespesas despesas;
    despesas.registrarDespesa("Luz", 300, "02/02/2026");

    std::vector<Usuario> moradores; // vazio
    ServicoRateio rateio;

    try {
        rateio.calcularRateio(despesas.listarDespesas(), moradores);
        std::cout << "✘ Erro: rateio inválido foi realizado\n";
    } catch (...) {
        std::cout << "✔ Rateio corretamente bloqueado\n";
    }

    std::cout << "---------------------------------\n";
}

/* ===============================
   MAIN
   =============================== */

int main() {
    testeRegistrarDespesaValida();
    testeRegistrarDespesaSemValor();
    testeRateioComMoradores();
    testeRateioSemMoradores();
    return 0;
}
