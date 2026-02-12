#include <iostream>
#include "services/ServicoDespesas.h"

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

int main() {
    testeRegistrarDespesaValida();
    testeRegistrarDespesaSemValor();

    return 0;
}
