#include "ServicoRateio.h"
#include "../infra/factory/Factory.h"
#include <stdexcept>

ServicoRateio::ServicoRateio()
    : strategy(infra::factory::createEqualRateio()) {}

ServicoRateio::ServicoRateio(std::shared_ptr<RateioStrategy> strat)
    : strategy(std::move(strat)) {}

std::vector<Rateio> ServicoRateio::calcularRateio(
    const std::vector<Despesa>& despesas,
    const std::vector<Usuario>& moradores) {

    // delegate to strategy
    return strategy->calcular(despesas, moradores);
}
