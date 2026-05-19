#ifndef PELICULA_H
#define PELICULA_H

#include "modelos/Produto.h"

class Pelicula : public Produto {
private:
    std::string modelo;
    std::string material;

public:
    Pelicula(int id, const std::string& nome, const std::string& descricao,
             double preco, int quantidade_estoque, const std::string& modelo, const std::string& material);

    TipoProduto getTipo() const override;
    void mostrar() const override;

    std::string getModelo() const;
    void setModelo(const std::string& modelo);
    std::string getMaterial() const;
    void setMaterial(const std::string& material);
};

#endif