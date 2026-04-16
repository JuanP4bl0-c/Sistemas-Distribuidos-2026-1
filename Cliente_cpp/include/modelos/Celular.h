#ifndef CELULAR_H
#define CELULAR_H

#include "modelos/Produto.h"

class Celular : public Produto {
private:
    std::string marca;
    std::string modelo;

public:
    Celular(int id,
            const std::string& nome,
            const std::string& descricao,
            double preco,
            int quantidade_estoque,
            const std::string& marca,
            const std::string& modelo);

    TipoProduto getTipo() const override;
    void mostrar() const override;

    // Getters e Setters
    std::string getMarca() const;
    std::string getModelo() const;
    void setMarca(const std::string& marca);
    void setModelo(const std::string& modelo);
};

#endif // CELULAR_H