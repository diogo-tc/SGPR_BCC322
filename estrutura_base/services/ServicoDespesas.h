#ifndef SERVICO_DESPESAS_H
#define SERVICO_DESPESAS_H

#include <vector>
#include <string>
#include "Despesa.h"

class ServicoDespesas {
private:
    std::vector<Despesa> despesas;

public:
    bool registrarDespesa(const std::string& descricao,
                          double valor,
                          const std::string& data);

    const std::vector<Despesa>& listarDespesas() const;
};

#endif
