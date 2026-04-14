#include "modelos/Pelicula.h"
#include <string>
#include <iostream>


Pelicula::Pelicula(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque, const std::string& modelo, const std::string& material)
                    : Produto(id, nome, descricao, preco, quantidade_estoque), modelo(modelo), material(material) {
}


TipoProduto Pelicula::getTipo() const {
    return TipoProduto::PELICULA;
}

void Pelicula::mostrar() const {
    Produto::mostrar();
    std::cout << "Modelo: " << modelo << std::endl;
    std::cout << "Material: " << material << std::endl;
}

std::string Pelicula::getModelo() const {
    return modelo;
}

void Pelicula::setModelo(const std::string& modelo) {
    this->modelo = modelo;
}

std::string Pelicula::getMaterial() const {
    return material;
}

void Pelicula::setMaterial(const std::string& material) {
    this->material = material;
}




