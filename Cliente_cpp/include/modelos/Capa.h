#ifndef   CAPA_H
#define   CAPA_H

#include <string>
#include "Produto.h"

class Capa : public Produto {
private:
    std::string material;
    std::string modelo;
public:
    Capa(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque, std::string material, std::string modelo);

    std::string getMaterial() const;
    void setMaterial(const std::string& material);
    std::string getModelo() const;
    void setModelo(const std::string& modelo);
    void mostrar() const override;
};

#endif // CAPA_H