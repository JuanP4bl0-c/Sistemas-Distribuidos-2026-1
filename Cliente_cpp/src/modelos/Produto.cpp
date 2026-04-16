#include "modelos/Produto.h"

// 🔹 Construtor
Produto::Produto(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque)
                : id(id), nome(nome), descricao(descricao), preco(preco), quantidade_estoque(quantidade_estoque) {}

// 🔹 Retorna o tipo base
TipoProduto Produto::getTipo() const {
    return TipoProduto::PRODUTO;
}

// 🔹 Exibição padrão
void Produto::mostrar() const {
    std::cout << "ID: " << id
              << " | Nome: " << nome
              << " | Descrição: " << descricao
              << " | Preço: R$ " << preco
              << " | Quantidade em Estoque: " << quantidade_estoque
              << std::endl;
}

// 🔹 Getters
int Produto::getId() const { return id; }
std::string Produto::getNome() const { return nome; }
std::string Produto::getDescricao() const { return descricao; }
double Produto::getPreco() const { return preco; }
int Produto::getQuantidadeEstoque() const { return quantidade_estoque; }

// 🔹 Setters
void Produto::setId(int id) { this->id = id; }
void Produto::setNome(const std::string& nome) { this->nome = nome; }
void Produto::setDescricao(const std::string& descricao) { this->descricao = descricao; }
void Produto::setPreco(double preco) { this->preco = preco; }
void Produto::setQuantidadeEstoque(int quantidade) { this->quantidade_estoque = quantidade; }
