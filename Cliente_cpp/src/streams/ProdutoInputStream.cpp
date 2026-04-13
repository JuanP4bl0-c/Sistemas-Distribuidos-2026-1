#include "streams/ProdutoInputStream.h"
#include <stdexcept>

ProdutoInputStream::ProdutoInputStream(std::istream& in) : in(in) {}

int ProdutoInputStream::readInt() {
    int value;
    in.read(reinterpret_cast<char*>(&value), sizeof(int));
    if (!in)
        throw std::runtime_error("Erro ao ler inteiro do stream.");
    return value;
}

double ProdutoInputStream::readDouble() {
    double value;
    in.read(reinterpret_cast<char*>(&value), sizeof(double));
    if (!in)
        throw std::runtime_error("Erro ao ler double do stream.");
    return value;
}

std::string ProdutoInputStream::readString() {
    int size = readInt();
    if (size < 0)
        throw std::runtime_error("Tamanho de string inválido.");

    std::string str(size, '\0');
    in.read(&str[0], size);
    if (!in)
        throw std::runtime_error("Erro ao ler string do stream.");
    return str;
}

std::vector<Produto> ProdutoInputStream::read() {
    produtos.clear();

    int qtd = readInt();

    for (int i = 0; i < qtd; ++i) {
        int id = readInt();
        std::string nome = readString();
        std::string descricao = readString();
        double preco = readDouble();
        int estoque = readInt();

        produtos.emplace_back(id, nome, descricao, preco, estoque);
    }

    return produtos;
}