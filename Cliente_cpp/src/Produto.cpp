#include Produto.h

Produto::Produto(int id, std::string nome, double preco) {
    this->id = id;
    this->nome = nome;
    this->preco = preco;
}

int Produto::getId() {
    return id;
}

std::string Produto::getNome() {
    return nome;
}

double Produto::getPreco() {
    return preco;
}

void Produto::setId(int id) {
    this->id = id;
}

void Produto::setNome(std::string nome) {
    this->nome = nome;
}

void Produto::setPreco(double preco) {
    this->preco = preco;
}

void mostrarProduto(Produto produto) {
    std::cout << "ID: " << produto.getId() << " | Nome: " << produto.getNome() << " | Preço: R$" << produto.getPreco() << std::endl;
}

