#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <iostream>
#include <memory> // Necessário para std::shared_ptr
#include "TipoProduto.h"
#include "Vendas.h"  // Sua nova interface
#include "Vendedor.h"   // Sua nova classe Vendedor

// Classe base que agora implementa Vendas
class Produto : public Vendas{
protected:
    int id;
    std::string nome;
    std::string descricao;
    double preco;
    int quantidade_estoque;
    
    // Agregação: Produto possui um Vendedor
    std::shared_ptr<Vendedor> vendedor;

public:
    Produto(int id,
            const std::string& nome,
            const std::string& descricao,
            double preco,
            int quantidade_estoque);

    virtual ~Produto() = default;

    // --- Métodos de Vendas ---
    // Você deve implementar estes métodos em Produto.cpp
    virtual double calcularPrecoFinal() override;
    virtual std::string obterResumoVenda() override;

    // --- Métodos da Classe ---
    virtual TipoProduto getTipo() const;
    virtual void mostrar() const;

    // Getters e Setters
    int getId() const;
    std::string getNome() const;
    std::string getDescricao() const;
    double getPreco() const;
    int getQuantidadeEstoque() const;
    
    // Getter e Setter da Agregação
    std::shared_ptr<Vendedor> getVendedor() const;
    void setVendedor(std::shared_ptr<Vendedor> v);

    void setId(int id);
    void setNome(const std::string& nome);
    void setDescricao(const std::string& descricao);
    void setPreco(double preco);
    void setQuantidadeEstoque(int quantidade_estoque);
};

#endif // PRODUTO_H