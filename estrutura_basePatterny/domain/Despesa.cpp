#include "Despesa.h"

Despesa::Despesa(const std::string& descricao,
                 double valor,
                 const std::string& data)
    : descricao(descricao), valor(valor), data(data), paga(false) {}

std::string Despesa::getDescricao() const {
    return descricao;
}

double Despesa::getValor() const {
    return valor;
}

std::string Despesa::getData() const {
    return data;
}

bool Despesa::estaPaga() const {
    return paga;
}

void Despesa::marcarComoPaga() {
    paga = true;
}
