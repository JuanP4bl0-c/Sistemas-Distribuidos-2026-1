#ifndef REQUEST_H
#define REQUEST_H

#include "modelos/Produto.h"
#include <vector>
#include <memory>

class Request {
public:
    // Já implementado (Opção 2 - Adicionar)
    static std::vector<char> buildAddProdutos(const std::vector<std::shared_ptr<Produto>>& produtos);

    // NOVO: (Opção 1 - Listar)
    static std::vector<char> buildListProdutos();

    // NOVO: (Opção 3 - Remover)
    static std::vector<char> buildRemoveProduto(int id);
};

#endif // REQUEST_H