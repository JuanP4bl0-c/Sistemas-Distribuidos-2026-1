#ifndef CAPA_H
#define CAPA_H

#include "modelos/Produto.h"

class Capa : public Produto {
private:
    std::string material;
    std::string modelo;

public:
    Capa(int id, const std::string& nome, const std::string& descricao,
         double preco, int quantidade_estoque, const std::string& material, const std::string& modelo);

    TipoProduto getTipo() const override;
    void mostrar() const override;

    std::string getMaterial() const;
    std::string getModelo() const;
    void setMaterial(const std::string& material);
    void setModelo(const std::string& modelo);
};

#endif