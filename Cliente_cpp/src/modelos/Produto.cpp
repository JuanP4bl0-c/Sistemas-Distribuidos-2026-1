#include "modelos/Produto.h"

<<<<<<< Updated upstream
<<<<<<< HEAD
// Construtor: inicializa campos base do produto
=======
// Construtor: inicializa campos base do produto (o vendedor inicia como nullptr)
>>>>>>> Stashed changes
Produto::Produto(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque)
                : id(id), nome(nome), descricao(descricao), preco(preco), quantidade_estoque(quantidade_estoque), vendedor(nullptr) {}

// --- Implementação da Interface IVendavel ---

double Produto::calcularPrecoFinal() {
    // Exemplo de lógica: o preço final é o preço base
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

<<<<<<< Updated upstream
// Retorna o tipo base do produto
=======
// 🔹 Construtor
Produto::Produto(int id, const std::string& nome, const std::string& descricao, double preco, int quantidade_estoque)
                : id(id), nome(nome), descricao(descricao), preco(preco), quantidade_estoque(quantidade_estoque) {}

// 🔹 Retorna o tipo base
>>>>>>> Entrega_2_Invocacao_Remota
=======
>>>>>>> Stashed changes
TipoProduto Produto::getTipo() const {
    return TipoProduto::PRODUTO;
}

<<<<<<< Updated upstream
<<<<<<< HEAD
// Exibição padrão: imprime informações básicas do produto
=======
// 🔹 Exibição padrão
>>>>>>> Entrega_2_Invocacao_Remota
=======
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
<<<<<<< HEAD
// Getters
=======
// 🔹 Getters
>>>>>>> Entrega_2_Invocacao_Remota
=======
// Getters e Setters básicos
>>>>>>> Stashed changes
int Produto::getId() const { return id; }
std::string Produto::getNome() const { return nome; }
std::string Produto::getDescricao() const { return descricao; }
double Produto::getPreco() const { return preco; }
int Produto::getQuantidadeEstoque() const { return quantidade_estoque; }

// Getter e Setter da Agregação
std::shared_ptr<Vendedor> Produto::getVendedor() const { return vendedor; }
void Produto::setVendedor(std::shared_ptr<Vendedor> v) { this->vendedor = v; }

void Produto::setId(int id) { this->id = id; }
void Produto::setNome(const std::string& nome) { this->nome = nome; }
void Produto::setDescricao(const std::string& descricao) { this->descricao = descricao; }
void Produto::setPreco(double preco) { this->preco = preco; }
<<<<<<< Updated upstream
<<<<<<< HEAD
void Produto::setQuantidadeEstoque(int quantidade) { this->quantidade_estoque = quantidade; }
=======
void Produto::setQuantidadeEstoque(int quantidade) { this->quantidade_estoque = quantidade; }
>>>>>>> Entrega_2_Invocacao_Remota
=======
void Produto::setQuantidadeEstoque(int quantidade) { this->quantidade_estoque = quantidade; }
>>>>>>> Stashed changes
