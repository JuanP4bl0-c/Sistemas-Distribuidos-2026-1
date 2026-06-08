#ifndef PRODUTO_API_H
#define PRODUTO_API_H

#include <memory>
#include <string>
#include "modelos/Vendedor.h"
#include "modelos/Produto.h"

class ProdutoAPI {
private:
    std::string baseUrl;

public:
    ProdutoAPI();
    ~ProdutoAPI();

    void listarProdutos(std::shared_ptr<Vendedor> gestorLogado);
    void adicionarProduto(std::shared_ptr<Produto> prod);
    void deletarProduto(int id);
    void realizarVenda(int produtoId, int qtd, std::shared_ptr<Vendedor> vendedor);
};

#endif