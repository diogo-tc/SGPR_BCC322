#ifndef FUNCIONAL_H
#define FUNCIONAL_H

#include <cassert>
#include <vector>
#include <map>
#include <iostream>

#include <QSqlQuery>     // necessário para limpar tabela
#include <QSqlDatabase>  // garante acesso à conexão ativa

using namespace std;

#include "../../src/lib/infra/factory/Factory.h"

// ================================
// Testes de Despesas
// ================================
void testeRegistrarDespesaValida();
void testeRegistrarDespesaSemValor();

// ================================
// Testes de Extrato
// ================================
void testeExtratoComSaldoInicial();
void testeExtratoSemRateio();

// ================================
// Testes de Rateio
// ================================
void testeRateioComMoradores();
void testeRateioSemMoradores();

#endif