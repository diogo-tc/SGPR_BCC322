#include "unit_despesas.h"
#include "unit_rateio.h"
#include "unit_extrato.h"
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
