#include "Factory.h"

namespace infra {
namespace factory {

std::unique_ptr<IDespesaRepository> createInMemoryDespesaRepository() {
    return std::make_unique<InMemoryDespesaRepository>();
}

std::shared_ptr<IRateio> createEqualRateio() {
    return std::make_shared<EqualRateio>();
}

ServicoDespesas createServicoDespesas() {
    return ServicoDespesas(createInMemoryDespesaRepository());
}

ServicoRateio createServicoRateio() {
    return ServicoRateio(createEqualRateio());
}

ServicoExtrato createServicoExtrato() {
    return ServicoExtrato();
}

} // namespace factory
} // namespace infra
