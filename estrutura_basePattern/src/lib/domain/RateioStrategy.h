#ifndef RATEIO_STRATEGY_H
#define RATEIO_STRATEGY_H

#include <vector>
#include "Despesa.h"
#include "Usuario.h"
#include "Rateio.h"

class RateioStrategy {
public:
    virtual ~RateioStrategy() = default;

    virtual std::vector<Rateio> calcular(
        const std::vector<Despesa>& despesas,
        const std::vector<Usuario>& moradores
    ) const = 0;
};

#endif
