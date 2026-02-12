#ifndef EQUAL_RATEIO_H
#define EQUAL_RATEIO_H

#include "RateioStrategy.h"

class EqualRateio : public RateioStrategy {
public:
    std::vector<Rateio> calcular(
        const std::vector<Despesa>& despesas,
        const std::vector<Usuario>& moradores
    ) const override;
};

#endif
