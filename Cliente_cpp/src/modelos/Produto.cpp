#include "modelos/Produto.h"

#include <iostream>

Produto::Produto(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque) {
    this->id = id;
    this->nome = nome;
    this->descricao = descricao;
    this->preco = preco;
    this->quantidade_estoque = quantidade_estoque;
}

int Produto::getId() const {
    return id;
}
std::string Produto::getNome() const {
    return nome;
}
std::string Produto::getDescricao() const {
    return descricao;
}
float Produto::getPreco() const {
    return preco;
}
int Produto::getQuantidadeEstoque() const {
    return quantidade_estoque;
}

void Produto::setId(int id) {
    this->id = id;
}
void Produto::setNome(const std::string& nome) {
    this->nome = nome;
}
void Produto::setDescricao(const std::string& descricao) {
    this->descricao = descricao;
}
void Produto::setPreco(float preco) {
    this->preco = preco;
}
void Produto::setQuantidadeEstoque(int quantidade_estoque) {
    this->quantidade_estoque = quantidade_estoque;
}

void Produto::mostrar() const {
    std::cout << "ID: " << id << " | Nome: " << nome << " | Descrição: " << descricao << " | Preco: R$" << preco << " | Quantidade em Estoque: " << quantidade_estoque << std::endl;
}
