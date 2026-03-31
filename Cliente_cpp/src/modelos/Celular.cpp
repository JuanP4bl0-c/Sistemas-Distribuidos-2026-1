#include "Celular.h"
#include <string>
#include <iostream>

Celular::Celular(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque, std::string marca, std::string modelo) : Produto(id, nome, descricao, preco, quantidade_estoque) {
    this->marca = marca;
    this->modelo = modelo;
}

std::string Celular::getMarca() const {
    return marca;
}
std::string Celular::getModelo() const {
    return modelo;
}

void Celular::setMarca(const std::string& marca) {
    this->marca = marca;
}
void Celular::setModelo(const std::string& modelo) {
    this->modelo = modelo;
}

void Celular::mostrar() const {
    std::cout << "ID: " << id << 
    "\n Nome: " << nome << 
    "\n Descrição: " << descricao << 
    "\n Marca: " << marca << 
    "\n Modelo: " << modelo << 
    "\n Preco: R$" << preco << 
    "\n Quantidade em Estoque: " << quantidade_estoque << std::endl;

}