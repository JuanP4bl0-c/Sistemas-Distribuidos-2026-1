#include "modelos/Celular.h"
#include <iostream>

Celular::Celular(int id,
                 const std::string& nome,
                 const std::string& descricao,
                 double preco,
                 int quantidade_estoque,
                 const std::string& marca,
                 const std::string& modelo)
    : Produto(id, nome, descricao, preco, quantidade_estoque),
      marca(marca),
      modelo(modelo) {}

TipoProduto Celular::getTipo() const {
    return TipoProduto::CELULAR;
}

void Celular::mostrar() const {
    Produto::mostrar();
    std::cout << "Marca: " << marca
              << " | Modelo: " << modelo << std::endl;
}

std::string Celular::getMarca() const { return marca; }
std::string Celular::getModelo() const { return modelo; }

void Celular::setMarca(const std::string& marca) {
    this->marca = marca;
}

void Celular::setModelo(const std::string& modelo) {
    this->modelo = modelo;
}