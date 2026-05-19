#include "modelos/Produto.h"

<<<<<<< HEAD
// Construtor: inicializa campos base do produto
Produto::Produto(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque)
                : id(id), nome(nome), descricao(descricao), preco(preco), quantidade_estoque(quantidade_estoque) {}

// Retorna o tipo base do produto
=======
// 🔹 Construtor
Produto::Produto(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque)
                : id(id), nome(nome), descricao(descricao), preco(preco), quantidade_estoque(quantidade_estoque) {}

// 🔹 Retorna o tipo base
>>>>>>> Entrega_2_Invocacao_Remota
TipoProduto Produto::getTipo() const {
    return TipoProduto::PRODUTO;
}

<<<<<<< HEAD
// Exibição padrão: imprime informações básicas do produto
=======
// 🔹 Exibição padrão
>>>>>>> Entrega_2_Invocacao_Remota
void Produto::mostrar() const {
    std::cout << "ID: " << id
              << " | Nome: " << nome
              << " | Descrição: " << descricao
              << " | Preço: R$ " << preco
              << " | Quantidade em Estoque: " << quantidade_estoque
              << std::endl;
}

<<<<<<< HEAD
// Getters
=======
// 🔹 Getters
>>>>>>> Entrega_2_Invocacao_Remota
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
<<<<<<< HEAD
void Produto::setQuantidadeEstoque(int quantidade) { this->quantidade_estoque = quantidade; }
=======
void Produto::setQuantidadeEstoque(int quantidade) { this->quantidade_estoque = quantidade; }
>>>>>>> Entrega_2_Invocacao_Remota
