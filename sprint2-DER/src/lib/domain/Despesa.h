#ifndef DESPESA_H
#define DESPESA_H

#include <string>

class Despesa {
private:
    std::string descricao;
    double valor;
    std::string data;
    bool paga;

public:
    Despesa(const std::string& descricao,
            double valor,
            const std::string& data);

    std::string getDescricao() const;
    double getValor() const;
    std::string getData() const;

    bool estaPaga() const;
    void marcarComoPaga();
};

#endif
