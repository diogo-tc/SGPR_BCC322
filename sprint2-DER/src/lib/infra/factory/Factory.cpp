#include "Factory.h"
#include "../persistence/SQLiteDespesaRepository.h"

namespace infra {
namespace factory {

std::unique_ptr<IDespesaRepository> createSQLiteDespesaRepository() {
    return std::make_unique<SQLiteDespesaRepository>();
}

std::shared_ptr<IRateio> createEqualRateio() {
    return std::make_shared<EqualRateio>();
}

ServicoDespesas createServicoDespesas() {
    return ServicoDespesas(createSQLiteDespesaRepository());
}

ServicoRateio createServicoRateio() {
    return ServicoRateio(createEqualRateio());
}

ServicoExtrato createServicoExtrato() {
    return ServicoExtrato();
}

} // namespace factory
} // namespace infra
