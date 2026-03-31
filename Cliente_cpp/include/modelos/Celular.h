#ifndef CELULAR_H
#define CELULAR_H

#include <string>
#include "Produto.h"

class Celular : public Produto {
private:
    std::string marca;
    std::string modelo;
public:
    Celular(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque, std::string marca, std::string modelo);

    std::string getMarca() const;
    std::string getModelo() const;
    void setMarca(const std::string& marca);
    void setModelo(const std::string& modelo);
    void mostrar() const override;
};

#endif // CELULAR_H