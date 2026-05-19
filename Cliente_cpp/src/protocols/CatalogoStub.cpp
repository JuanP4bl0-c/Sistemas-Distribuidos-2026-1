#include "protocols/CatalogoStub.h"
#include "protocols/Request.h"
#include "protocols/Reply.h"
#include "streams/ProdutoInputStream.h"
#include <sstream>
#include <iostream>

CatalogoStub::CatalogoStub(CorbaClient& clienteRede, const std::string& objectReference)
    : transporteCORBA(clienteRede), objectRef(objectReference) {}

// Operação 1 — LISTAR
// Envia uma requisição JSON para o despachante Java e recebe o envelope
// de resposta em JSON. O stub imprime o JSON recebido e retorna um vetor
// vazio (a desserialização completa fica a cargo do despachante/esqueleto).
std::vector<std::shared_ptr<Produto>> CatalogoStub::listarProdutos() {
    // 1) Prepara a requisição JSON de listagem
    auto requestData = Request::buildListProdutos();

    // 2) Despacha via transporte CORBA usando methodId = 1
    std::vector<char> replyData = transporteCORBA.doOperation(objectRef, 1, requestData);

    if (replyData.empty()) {
        std::cout << "\n[Stub] Resposta vazia recebida do servidor.\n";
        return std::vector<std::shared_ptr<Produto>>();
    }

    // 3) Converte os bytes de resposta para a string JSON enviada pelo servidor Java
    std::string jsonResposta(replyData.begin(), replyData.end());
    
    // Exibe o envelope RPC (JSON) recebido do esqueleto Java
    std::cout << "\n>>> Envelope RPC de Resposta (JSON recebido do Esqueleto Java): <<<\n";
    std::cout << jsonResposta << "\n";

    // Retorna vetor vazio: a exibição textual do JSON satisfaz o requisito atual.
    return std::vector<std::shared_ptr<Produto>>(); 
}

// ➔ OPERAÇÃO 2: ADICIONAR
std::string CatalogoStub::adicionarProdutos(const std::vector<std::shared_ptr<Produto>>& produtos) {
    auto requestData = Request::buildAddProdutos(produtos);
    
    // Dispara o JSON completo dentro do campo arguments do CORBA
    std::vector<char> replyData = transporteCORBA.doOperation("CatalogoRemoto", 2, requestData);

    if (replyData.empty()) return "Erro: Sem resposta do servidor.";

    // A resposta já é a string JSON do Java! Convertemos e retornamos direto para o main
    return std::string(replyData.begin(), replyData.end());
}

// ➔ OPERAÇÃO 3: REMOVER (Atualizado para ler resposta em String JSON)
std::string CatalogoStub::removerProduto(int id) {
    // 1. O Stub empacota o ID binário no envelope JSON
    auto requestData = Request::buildRemoveProduto(id);

    // 2. Stub envia os dados com o methodId = 3
    std::vector<char> replyData = transporteCORBA.doOperation(objectRef, 3, requestData);

    if (replyData.empty()) {
        return "Erro: Sem resposta do servidor.";
    }

    // 3. ✅ CORREÇÃO: Transforma os bytes recebidos diretamente na String JSON de resposta
    return std::string(replyData.begin(), replyData.end());
}

