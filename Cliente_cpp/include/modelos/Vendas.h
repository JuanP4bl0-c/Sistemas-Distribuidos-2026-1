#ifndef VENDAS_H
#define VENDAS_H
#include <string>

class Vendas{
public:
    virtual ~Vendas() {}
    virtual double calcularPrecoFinal() = 0;
    virtual std::string obterResumoVenda() = 0;
};
#endif