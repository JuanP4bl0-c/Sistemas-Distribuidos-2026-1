#include "modelos/PowerBank.h"
#include <string>
#include <iostream>

PowerBank::PowerBank(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque, int capacidade, const std::string& modelo, const std::string& marca)
                        : Produto(id, nome, descricao, preco, quantidade_estoque), capacidade(capacidade), modelo(modelo), marca(marca) {}

TipoProduto PowerBank::getTipo() const {
    return TipoProduto::POWERBANK;
}

int PowerBank::getCapacidade() const {
    return capacidade;
}

void PowerBank::setCapacidade(int capacidade) {
    this->capacidade = capacidade;
}

std::string PowerBank::getModelo() const {
    return modelo;
}

void PowerBank::setModelo(const std::string& modelo) {
    this->modelo = modelo;
}

std::string PowerBank::getMarca() const {
    return marca;
}

void PowerBank::setMarca(const std::string& marca) {
    this->marca = marca;
}

void PowerBank::mostrar() const {
    Produto::mostrar();
    std::cout << "Capacidade: " << capacidade << " mAh" << std::endl;
    std::cout << "Modelo: " << modelo << std::endl;
    std::cout << "Marca: " << marca << std::endl;
}