#include "EqualRateio.h"
#include <stdexcept>

std::vector<Rateio> EqualRateio::calcular(
    const std::vector<Despesa>& despesas,
    const std::vector<Usuario>& moradores) const {

    if (moradores.empty()) {
        throw std::runtime_error("Nao e possivel realizar o rateio sem moradores ativos");
    }

    double total = 0.0;
    for (const auto& d : despesas) {
        total += d.getValor();
    }

    double valorPorMorador = total / moradores.size();

    std::vector<Rateio> resultado;
    for (const auto& m : moradores) {
        resultado.emplace_back(m.getNome(), valorPorMorador);
    }

    return resultado;
}
