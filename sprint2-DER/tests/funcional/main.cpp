#include "funcional_despesas.h"
#include "funcional_rateio.h"
#include "funcional_extrato.h"
#include <iostream>


int main() {
    std::cout << "comecando teste\n";
    testeRegistrarDespesaValida();
    testeRegistrarDespesaSemValor();

    testeRateioComMoradores();
    testeRateioSemMoradores();

    testeExtratoComSaldoInicial();
    testeExtratoSemRateio();
    std::cout << "finalizando teste\n";

    return 0;
}
