#ifndef EXTRATO_H
#define EXTRATO_H

#include <string>

class Extrato {
private:
    std::string usuario;
    double saldoInicial;
    double valorRateio;
    double saldoFinal;

public:
    Extrato(const std::string& usuario,
            double saldoInicial,
            double valorRateio);

    std::string getUsuario() const;
    double getSaldoInicial() const;
    double getValorRateio() const;
    double getSaldoFinal() const;
};

#endif
