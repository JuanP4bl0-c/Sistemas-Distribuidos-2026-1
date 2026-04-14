#ifndef POWERBANK_H
#define POWERBANK_H

#include "modelos/Produto.h"

class PowerBank : public Produto {
private:
    int capacidade; // mAh
    std::string modelo;
    std::string marca;

public:
    PowerBank(int id, const std::string& nome, const std::string& descricao,
              double preco, int quantidade_estoque, int capacidade,
              const std::string& modelo, const std::string& marca);

    TipoProduto getTipo() const override;
    void mostrar() const override;

    int getCapacidade() const;
    void setCapacidade(int capacidade);
    std::string getModelo() const;
    void setModelo(const std::string& modelo);
    std::string getMarca() const;
    void setMarca(const std::string& marca);
};

#endif