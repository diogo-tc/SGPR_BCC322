#ifndef IEXTRATO_H
#define IEXTRATO_H

#include <vector>
#include <map>
#include <string>
#include "../../domain/Rateio.h"
#include "../../domain/Extrato.h"

class IExtrato {
public:
    virtual ~IExtrato() = default;

    virtual std::vector<Extrato> gerarExtrato(
        const std::vector<Rateio>& rateios,
        const std::map<std::string, double>& saldoInicialPorUsuario
    ) = 0;
};

#endif
