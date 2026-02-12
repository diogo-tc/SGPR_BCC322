#ifndef IDESPESA_REPOSITORY_H
#define IDESPESA_REPOSITORY_H

#include <vector>
#include "../../domain/Despesa.h"

class IDespesaRepository {
public:
    virtual ~IDespesaRepository() = default;

    virtual void adicionar(const Despesa& d) = 0;
    virtual const std::vector<Despesa>& listar() const = 0;
};

#endif
