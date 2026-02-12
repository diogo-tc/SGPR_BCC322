#ifndef SERVICO_RATEIO_H
#define SERVICO_RATEIO_H

#include <vector>
#include <memory>
#include "../domain/Despesa.h"
#include "../domain/Usuario.h"
#include "../domain/Rateio.h"
#include "../domain/RateioStrategy.h"

class ServicoRateio {
private:
    std::shared_ptr<RateioStrategy> strategy;

public:
    ServicoRateio();
    explicit ServicoRateio(std::shared_ptr<RateioStrategy> strat);

    std::vector<Rateio> calcularRateio(
        const std::vector<Despesa>& despesas,
        const std::vector<Usuario>& moradores
    );
};

#endif
