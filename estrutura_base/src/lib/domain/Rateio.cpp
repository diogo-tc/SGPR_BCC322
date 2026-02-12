#include "Rateio.h"

Rateio::Rateio(const std::string& usuario, double valor)
    : usuario(usuario), valor(valor) {}

std::string Rateio::getUsuario() const {
    return usuario;
}

double Rateio::getValor() const {
    return valor;
}
