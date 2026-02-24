#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "../repository/IDespesaRepository.h"
#include "../Interfaces/IRateio.h"
#include "../../services/ServicoDespesas.h"
#include "../../services/ServicoRateio.h"
#include "../../services/ServicoExtrato.h"
#include "../repository/InMemoryDespesaRepository.h"
#include "../../domain/EqualRateio.h"


namespace infra {
namespace factory {

std::unique_ptr<IDespesaRepository> createSQLiteDespesaRepository();
std::shared_ptr<IRateio> createEqualRateio();

ServicoDespesas createServicoDespesas();
ServicoRateio createServicoRateio();
ServicoExtrato createServicoExtrato();

} // namespace factory
} // namespace infra

#endif
