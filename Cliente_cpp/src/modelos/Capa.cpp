#include "modelos/Capa.h"
#include <string>
#include <iostream>

Capa::Capa(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque, std::string material, std::string modelo) : Produto(id, nome, descricao, preco, quantidade_estoque) {
    this->material = material;
    this->modelo = modelo;
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

void Capa::mostrar() const {
    std::cout << "ID: " << id << 
    "\n Nome: " << nome << 
    "\n Descrição: " << descricao << 
    "\n Material: " << material << 
    "\n Modelo: " << modelo << 
    "\n Preco: R$" << preco << 
    "\n Quantidade em Estoque: " << quantidade_estoque << std::endl;

}


