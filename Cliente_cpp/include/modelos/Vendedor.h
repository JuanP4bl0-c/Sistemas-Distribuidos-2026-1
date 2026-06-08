#ifndef VENDEDOR_H
#define VENDEDOR_H
#include <string>

class Vendedor {
public:
    std::string nome;
    std::string id;
    Vendedor(std::string n, std::string m) : nome(n), id(m) {}
};
#endif