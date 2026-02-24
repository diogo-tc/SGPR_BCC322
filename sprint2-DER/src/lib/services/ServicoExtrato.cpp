#include "ServicoExtrato.h"
#include <stdexcept>

std::vector<Extrato> ServicoExtrato::gerarExtrato(
    const std::vector<Rateio>& rateios,
    const std::map<std::string, double>& saldoInicialPorUsuario) {

    if (rateios.empty()) {
        throw std::runtime_error(
            "Nao e possivel gerar extrato sem rateio"
        );
    }

    std::vector<Extrato> extratos;

    for (const auto& r : rateios) {
        double saldoInicial = 0.0;

        auto it = saldoInicialPorUsuario.find(r.getUsuario());
        if (it != saldoInicialPorUsuario.end()) {
            saldoInicial = it->second;
        }

        extratos.emplace_back(
            r.getUsuario(),
            saldoInicial,
            r.getValor()
        );
    }

    return extratos;
}
