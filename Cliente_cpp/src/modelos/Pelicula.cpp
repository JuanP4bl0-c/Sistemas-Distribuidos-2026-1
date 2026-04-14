#include "modelos/Pelicula.h"
#include <string>
#include <iostream>

Pelicula::Pelicula(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque, std::string modelo, std::string material)
    : Produto(id, nome, descricao, preco, quantidade_estoque), modelo(modelo), material(material) {}

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

void Pelicula::mostrar() const {
    Produto::mostrar();
    std::cout << "Modelo: " << modelo << std::endl;
    std::cout << "Material: " << material << std::endl;
}