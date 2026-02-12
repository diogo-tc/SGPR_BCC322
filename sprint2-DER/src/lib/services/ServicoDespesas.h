#ifndef SERVICO_DESPESAS_H
#define SERVICO_DESPESAS_H

#include <vector>
#include <string>
#include <memory>
#include "../domain/Despesa.h"
#include "../infra/repository/IDespesaRepository.h"

class ServicoDespesas {
private:
    std::unique_ptr<IDespesaRepository> repo;

public:
    ServicoDespesas();
    explicit ServicoDespesas(std::unique_ptr<IDespesaRepository> repository);

    bool registrarDespesa(const std::string& descricao,
                          double valor,
                          const std::string& data);

    const std::vector<Despesa>& listarDespesas() const;
};

#endif
