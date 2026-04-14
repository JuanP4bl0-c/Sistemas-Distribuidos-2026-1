#include "modelos/Capa.h"
#include <string>
#include <iostream>

Capa::Capa(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque, const std::string& material)
            : Produto(id, nome, descricao, preco, quantidade_estoque), material(material) {}

TipoProduto Capa::getTipo() const {
    return TipoProduto::CAPA;
}

void Capa::mostrar() const {
    Produto::mostrar();
    std::cout << "Material: " << material << std::endl;
    
}

std::string Capa::getMaterial() const {
    return material;
}

void Capa::setMaterial(const std::string& material) {
    this->material = material;
}

