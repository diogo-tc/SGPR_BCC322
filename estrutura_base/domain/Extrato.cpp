#include "Extrato.h"

Extrato::Extrato(const std::string& usuario,
                 double saldoInicial,
                 double valorRateio)
    : usuario(usuario),
      saldoInicial(saldoInicial),
      valorRateio(valorRateio),
      saldoFinal(saldoInicial - valorRateio) {}

std::string Extrato::getUsuario() const {
    return usuario;
}

double Extrato::getSaldoInicial() const {
    return saldoInicial;
}

double Extrato::getValorRateio() const {
    return valorRateio;
}

double Extrato::getSaldoFinal() const {
    return saldoFinal;
}
