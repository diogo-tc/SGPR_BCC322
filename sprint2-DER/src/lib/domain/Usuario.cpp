#include "Usuario.h"

Usuario::Usuario(const std::string& nome) : nome(nome) {}

std::string Usuario::getNome() const {
    return nome;
}
