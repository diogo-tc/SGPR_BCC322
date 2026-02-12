#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "../repository/IDespesaRepository.h"
#include "../../domain/RateioStrategy.h"
#include "../../services/ServicoDespesas.h"
#include "../../services/ServicoRateio.h"
#include "../../services/ServicoExtrato.h"

namespace infra {
namespace factory {

std::unique_ptr<IDespesaRepository> createInMemoryDespesaRepository();
std::shared_ptr<RateioStrategy> createEqualRateio();

ServicoDespesas createServicoDespesas();
ServicoRateio createServicoRateio();
ServicoExtrato createServicoExtrato();

} // namespace factory
} // namespace infra

#endif
