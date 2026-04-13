#ifndef POWERBANK_H
#define POWERBANK_H

#include <string>
#include "Produto.h"

class PowerBank : public Produto {
private:
    int capacidade; // em mAh
    std::string modelo;
    std::string marca;

public:
    PowerBank(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque, int capacidade, std::string modelo, std::string marca);

    int getCapacidade() const;
    void setCapacidade(int capacidade);
    std::string getModelo() const;
    void setModelo(const std::string& modelo);
    std::string getMarca() const;
    void setMarca(const std::string& marca);
    void mostrar() const override;
};

#endif // POWERBANK_H