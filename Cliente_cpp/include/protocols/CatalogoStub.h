#ifndef CATALOGO_STUB_H
#define CATALOGO_STUB_H

#include <vector>
#include <memory>
#include <string>
#include "modelos/Produto.h"
#include "network/CORBA_Client.h" // Classe de transporte CORBA que criámos

class CatalogoStub {
private:
    CorbaClient& transporteCORBA; // Referência para a camada de transporte
    std::string objectRef;        // Identificador do objeto remoto ("CatalogoRemoto")

public:
    /// Construtor: vincula o `CatalogoStub` à camada de transporte CORBA.
    CatalogoStub(CorbaClient& clienteRede, const std::string& objectReference = "CatalogoRemoto");

    /// Solicita a listagem de produtos ao servidor e retorna vetor polimórfico.
    std::vector<std::shared_ptr<Produto>> listarProdutos();

    /// Envia pedido para adicionar produtos; retorna mensagem/resultado como string.
    std::string adicionarProdutos(const std::vector<std::shared_ptr<Produto>>& produtos);

    /// Solicita remoção de produto por `id`; retorna mensagem/resultado.
    std::string removerProduto(int id);
};

#endif // CATALOGO_STUB_H