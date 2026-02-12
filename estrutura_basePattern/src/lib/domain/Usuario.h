#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string nome;

public:
    explicit Usuario(const std::string& nome);
    std::string getNome() const;
};

#endif
