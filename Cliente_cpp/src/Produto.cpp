#include "Produto.h"

#include <iostream>

Produto::Produto(int id, std::string nome, double preco) {
    this->id = id;
    this->nome = nome;
    this->preco = preco;
}

int Produto::getId() const {
    return id;
}

std::string Produto::getNome() const {
    return nome;
}

double Produto::getPreco() const {
    return preco;
}

void Produto::setId(int id) {
    this->id = id;
}

void Produto::setNome(const std::string& nome) {
    this->nome = nome;
}

void Produto::setPreco(double preco) {
    this->preco = preco;
}

void Produto::mostrar() const {
    std::cout << "ID: " << id << " | Nome: " << nome << " | Preco: R$" << preco << std::endl;
}

