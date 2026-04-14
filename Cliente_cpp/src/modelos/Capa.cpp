#include "modelos/Capa.h"
#include <string>
#include <iostream>

Capa::Capa(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque, const std::string& material, const std::string& modelo)
            : Produto(id, nome, descricao, preco, quantidade_estoque), material(material), modelo(modelo) {}
TipoProduto Capa::getTipo() const {
    return TipoProduto::CAPA;
}

void Capa::mostrar() const {
    Produto::mostrar();
    std::cout << "Material: " << material << std::endl;
    std::cout << "Modelo: " << modelo << std::endl;
}


std::string Capa::getMaterial() const {
    return material;
}

void Capa::setMaterial(const std::string& material) {
    this->material = material;
}

std::string Capa::getModelo() const {
    return modelo;
}

void Capa::setModelo(const std::string& modelo) {
    this->modelo = modelo;
}
