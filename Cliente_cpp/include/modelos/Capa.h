#ifndef CAPA_H
#define CAPA_H

#include "modelos/Produto.h"

class Capa : public Produto {
private:
    std::string material;

public:
    Capa(int id, const std::string& nome, const std::string& descricao,
         double preco, int quantidade_estoque, const std::string& material);

    TipoProduto getTipo() const override;
    void mostrar() const override;

    std::string getMaterial() const;
    void setMaterial(const std::string& material);
};

#endif