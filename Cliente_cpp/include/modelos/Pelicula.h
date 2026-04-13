#ifndef PELICULA_H
#define PELICULA_H

#include <string>
#include "Produto.h"

class Pelicula : public Produto {
private:
    std::string modelo;
    std::string material;
public:
    Pelicula(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque, std::string modelo, std::string material);
    std::string getModelo() const;
    void setModelo(const std::string& modelo);
    std::string getMaterial() const;
    void setMaterial(const std::string& material);
    void mostrar() const override;
};

#endif // PELICULA_H
