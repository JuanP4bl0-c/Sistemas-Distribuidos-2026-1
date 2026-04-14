#ifndef PELICULA_H
#define PELICULA_H

#include "modelos/Produto.h"

class Pelicula : public Produto {
private:
    std::string tipo;

public:
    Pelicula(int id, const std::string& nome, const std::string& descricao,
             double preco, int quantidade_estoque, const std::string& tipo);

    TipoProduto getTipo() const override;
    void mostrar() const override;

    std::string getTipoPelicula() const;
    void setTipoPelicula(const std::string& tipo);
};

#endif