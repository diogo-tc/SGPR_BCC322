#ifndef FUNCIONAL_H
#define FUNCIONAL_H

#include <cassert>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#include "../../src/lib/infra/factory/Factory.h"

void testeRegistrarDespesaValida();
void testeRegistrarDespesaSemValor();

void testeExtratoComSaldoInicial();
void testeExtratoSemRateio();

void testeRateioComMoradores();
void testeRateioSemMoradores();

#endif 