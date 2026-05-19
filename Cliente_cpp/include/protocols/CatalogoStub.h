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
    // Construtor: Vincula o Stub ao transporte CORBA
    CatalogoStub(CorbaClient& clienteRede, const std::string& objectReference = "CatalogoRemoto");

    // Métodos de Negócio Abstratos (O main.cpp chamará estes métodos diretamente)
    std::vector<std::shared_ptr<Produto>> listarProdutos();
    std::string adicionarProdutos(const std::vector<std::shared_ptr<Produto>>& produtos);
    std::string removerProduto(int id);
};

#endif // CATALOGO_STUB_H