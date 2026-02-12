#ifndef IDESPESA_H
#define IDESPESA_H

#include <vector>
#include <string>
#include "../../domain/Despesa.h"

class IDespesa {
public:
    virtual ~IDespesa() = default;

    virtual bool registrarDespesa(const std::string& descricao,
                                  double valor,
                                  const std::string& data) = 0;

    virtual const std::vector<Despesa>& listarDespesas() const = 0;
};

#endif
