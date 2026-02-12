#ifndef EQUAL_RATEIO_H
#define EQUAL_RATEIO_H

#include "../infra/Interfaces/IRateio.h"

class EqualRateio : public IRateio {
public:
    std::vector<Rateio> calcular(
        const std::vector<Despesa>& despesas,
        const std::vector<Usuario>& moradores
    ) const override;
};

#endif
