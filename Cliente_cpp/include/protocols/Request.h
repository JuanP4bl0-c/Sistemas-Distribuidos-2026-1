#ifndef REQUEST_H
#define REQUEST_H

<<<<<<< HEAD
#include "modelos/Produto.h"
#include <vector>
#include <memory>

class Request {
public:
    /// Constrói o envelope JSON (bytes) para a operação ADICIONAR produtos.
    /// Formato esperado: objeto com `objectReference`, `methodId` e `arguments`.
    static std::vector<char> buildAddProdutos(const std::vector<std::shared_ptr<Produto>>& produtos);

    /// Constrói o envelope JSON (bytes) para a operação LISTAR produtos.
    static std::vector<char> buildListProdutos();

    /// Constrói o envelope JSON (bytes) para a operação REMOVER produto (por id).
    static std::vector<char> buildRemoveProduto(int id);
};

#endif // REQUEST_H
=======
#include <vector>
#include <memory>
#include <cstdint>
#include "modelos/Produto.h"

class Request {
public:
    static std::vector<char> buildAddProdutos(
        const std::vector<std::shared_ptr<Produto>>& produtos);
};

#endif
>>>>>>> Entrega_2_Invocacao_Remota
