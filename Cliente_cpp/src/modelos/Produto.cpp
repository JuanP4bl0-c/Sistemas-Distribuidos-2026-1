#include "modelos/Produto.h"

// Construtor: inicializa campos base do produto e define o vendedor como nullptr (segurança)
Produto::Produto(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque)
                : id(id), nome(nome), descricao(descricao), preco(preco), quantidade_estoque(quantidade_estoque), vendedor(nullptr) {}

// --- Implementação da Interface IVendavel ---

double Produto::calcularPrecoFinal() {
    return this->preco;
}

std::string Produto::obterResumoVenda() {
    std::string resumo = "Produto: " + this->nome + " | ";
    if (vendedor) {
        resumo += "Vendedor: " + vendedor->nome;
    } else {
        resumo += "Vendedor: Não atribuído";
    }
    return resumo;
}

// --- Métodos da Classe ---

// Retorna o tipo base do produto
TipoProduto Produto::getTipo() const {
    return TipoProduto::PRODUTO;
}

// Exibição padrão: imprime informações básicas e, se houver, o vendedor
void Produto::mostrar() const {
    std::cout << "ID: " << id
              << " | Nome: " << nome
              << " | Preço: R$ " << preco
              << " | Estoque: " << quantidade_estoque;
    
    if (vendedor) {
        std::cout << " | Vendedor: " << vendedor->nome;
    }
    std::cout << std::endl;
}

// Getters e Setters
int Produto::getId() const { return id; }
std::string Produto::getNome() const { return nome; }
std::string Produto::getDescricao() const { return descricao; }
double Produto::getPreco() const { return preco; }
int Produto::getQuantidadeEstoque() const { return quantidade_estoque; }

// Getter e Setter da Agregação (Vendedor)
std::shared_ptr<Vendedor> Produto::getVendedor() const { return vendedor; }
void Produto::setVendedor(std::shared_ptr<Vendedor> v) { this->vendedor = v; }

// Setters básicos
void Produto::setId(int id) { this->id = id; }
void Produto::setNome(const std::string& nome) { this->nome = nome; }
void Produto::setDescricao(const std::string& descricao) { this->descricao = descricao; }
void Produto::setPreco(double preco) { this->preco = preco; }
void Produto::setQuantidadeEstoque(int quantidade) { this->quantidade_estoque = quantidade; }