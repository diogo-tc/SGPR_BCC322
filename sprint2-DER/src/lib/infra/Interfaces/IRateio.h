#ifndef IRATEIO_H
#define IRATEIO_H

#include <vector>
#include "../../domain/Despesa.h"
#include "../../domain/Usuario.h"
#include "../../domain/Rateio.h"

class IRateio {
public:
    virtual ~IRateio() = default;

    virtual std::vector<Rateio> calcular(
        const std::vector<Despesa>& despesas,
        const std::vector<Usuario>& moradores
    ) const = 0;
};

#endif
