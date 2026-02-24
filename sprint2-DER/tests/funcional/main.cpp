#include "funcional.h"

int main() {

    testeRegistrarDespesaValida();
    testeRegistrarDespesaSemValor();
    std::cout << "Testes de despesas corretos!\n";

    testeRateioComMoradores();
    testeRateioSemMoradores();
    std::cout << "Testes de rateio corretos!\n";

    testeExtratoComSaldoInicial();
    testeExtratoSemRateio();
    std::cout << "Testes de extrato corretos!\n";

    std::cout << "Todos os testes passaram corretamente!!\n";
    
    return 0;
}
