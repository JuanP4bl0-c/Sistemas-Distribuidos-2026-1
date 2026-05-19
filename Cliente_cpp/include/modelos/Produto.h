#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <iostream>
#include "modelos/TipoProduto.h"

class Produto {
protected:
    int id;
    std::string nome;
    std::string descricao;
    double preco;
    int quantidade_estoque;

public:
    Produto(int id,
            const std::string& nome,
            const std::string& descricao,
            double preco,
            int quantidade_estoque);

    virtual ~Produto() = default;

    /// Retorna o tipo do produto (enum `TipoProduto`).
    virtual TipoProduto getTipo() const;

    /// Exibe informações do produto por `std::cout`.
    virtual void mostrar() const;

    // Getters
    int getId() const;
    std::string getNome() const;
    std::string getDescricao() const;
    double getPreco() const;
    int getQuantidadeEstoque() const;

    // Setters
    void setId(int id);
    void setNome(const std::string& nome);
    void setDescricao(const std::string& descricao);
    void setPreco(double preco);
    void setQuantidadeEstoque(int quantidade_estoque);
};

#endif // PRODUTO_H