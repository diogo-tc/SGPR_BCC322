#ifndef SERVICO_EXTRATO_H
#define SERVICO_EXTRATO_H

#include <vector>
#include <map>
#include "../domain/Rateio.h"
#include "../domain/Extrato.h"

class ServicoExtrato {
public:
    std::vector<Extrato> gerarExtrato(
        const std::vector<Rateio>& rateios,
        const std::map<std::string, double>& saldoInicialPorUsuario
    );
};

#endif
