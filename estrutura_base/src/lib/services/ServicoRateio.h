#ifndef SERVICO_RATEIO_H
#define SERVICO_RATEIO_H

#include <vector>
#include "../domain/Despesa.h"
#include "../domain/Usuario.h"
#include "../domain/Rateio.h"

class ServicoRateio {
public:
    std::vector<Rateio> calcularRateio(
        const std::vector<Despesa>& despesas,
        const std::vector<Usuario>& moradores
    );
};

#endif
