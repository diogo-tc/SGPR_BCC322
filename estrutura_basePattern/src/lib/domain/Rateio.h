#ifndef RATEIO_H
#define RATEIO_H

#include <string>

class Rateio {
private:
    std::string usuario;
    double valor;

public:
    Rateio(const std::string& usuario, double valor);

    std::string getUsuario() const;
    double getValor() const;
};

#endif
