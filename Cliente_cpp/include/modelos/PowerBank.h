#ifndef POWERBANK_H
#define POWERBANK_H

#include "modelos/Produto.h"

class PowerBank : public Produto {
private:
    std::string marca;
    std::string modelo;
    int capacidade; // mAh
    

public:
    PowerBank(int id, const std::string& nome, const std::string& descricao,
              double preco, int quantidade_estoque, const std::string& marca, const std::string& modelo, int capacidade);

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