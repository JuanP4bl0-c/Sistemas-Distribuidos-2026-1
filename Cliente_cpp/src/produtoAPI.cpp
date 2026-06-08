/**
 * @file ProdutoAPI.cpp
 * @brief Implementação do Cliente RESTful em C++ utilizando a biblioteca libcurl.
 * * Esta classe atua como um "Proxy" ou "Middleware" de comunicação. Ela abstrai 
 * a complexidade da rede, permitindo que a aplicação C++ interaja com o 
 * Servidor Java através de requisições HTTP (GET, POST, DELETE) e troca de 
 * mensagens no formato JSON (Marshalling/Unmarshalling).
 */

#include "produtoAPI.h" 
#include "utils/Config.h"
#include <iostream>
#include <string>
#include <curl/curl.h>

/**
 * @brief Função de Callback utilizada pela libcurl.
 * * Como a rede entrega os dados em pacotes (chunks) de bytes, o CURL chama 
 * esta função automaticamente cada vez que recebe um pedaço da resposta HTTP.
 * Nós pegamos esses bytes e anexamos (append) em uma string C++ normal.
 */
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// -------------------------------------------------------------------------
// CONSTRUTOR E DESTRUTOR (Gerenciamento de Ciclo de Vida da libcurl)
// -------------------------------------------------------------------------

ProdutoAPI::ProdutoAPI() {
    // Inicializa o motor do CURL globalmente no início do programa
    curl_global_init(CURL_GLOBAL_DEFAULT);
    try {
        Config configuracao("config/Config.txt");
        
        // Monta a baseUrl convertendo a porta (int) para string
        this->baseUrl = "http://" + configuracao.getIp() + ":" + std::to_string(configuracao.getPort());
        
        std::cout << "[Sistema] API inicializada. Apontando para: " << this->baseUrl << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Erro Crítico] Falha ao carregar configuração: " << e.what() << std::endl;
        // Fallback de segurança caso o config falhe
        this->baseUrl = "http://localhost:8000"; 
    }
}

ProdutoAPI::~ProdutoAPI() {
    // Libera os recursos de rede alocados pelo CURL ao encerrar a aplicação
    curl_global_cleanup();
}

// -------------------------------------------------------------------------
// MÉTODOS DE INTEGRAÇÃO RESTful (CRUD)
// -------------------------------------------------------------------------

/**
 * @brief Solicita o catálogo de produtos ao servidor. (Verbo HTTP: GET)
 * @param gestor Objeto Vendedor que representa o usuário logado (Contexto).
 */
void ProdutoAPI::listarProdutos(std::shared_ptr<Vendedor> gestor) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer; // Armazenará o JSON de resposta

    curl = curl_easy_init();
    if(curl) {
        std::cout << "\n[API] " << gestor->nome << " esta solicitando o catalogo de vendas..." << std::endl;
        
        // Define a URL (Endpoint REST)
        std::string url = this->baseUrl + "/api/produtos"; // 🔹 Usa a baseUrl
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // [CONTEXTO STATELESS] - API REST não guarda sessão. 
        // Passamos a identidade do gestor via Headers HTTP customizados.
        struct curl_slist *headers = NULL;
        std::string headerId = "X-Gestor-ID: " + gestor->id;
        std::string headerNome = "X-Gestor-Nome: " + gestor->nome;

        headers = curl_slist_append(headers, headerId.c_str());
        headers = curl_slist_append(headers, headerNome.c_str());
        
        // Aplica os cabeçalhos e configura o callback para receber a resposta
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Executa a requisição bloqueante
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            std::cerr << "[API] Erro de conexao (GET): " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "--- Itens do Catalogo de Vendas ---\n" << readBuffer << std::endl;
        }
        
        // Limpeza de memória local
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

/**
 * @brief Envia um novo produto para ser salvo no servidor. (Verbo HTTP: POST)
 * @param prod Ponteiro inteligente para o produto a ser salvo.
 */
void ProdutoAPI::adicionarProduto(std::shared_ptr<Produto> prod) {
    CURL *curl = curl_easy_init();
    if(curl) {
        std::cout << "\n[API] Enviando produto para o servidor..." << std::endl;
        
        // [MARSHALLING] - Serializando os dados do objeto C++ para uma string JSON
        std::string jsonPayload = "{"
            "\"tipo\":\"Produto\", "
            "\"id\":" + std::to_string(prod->getId()) + ", "
            "\"nome\":\"" + prod->getNome() + "\", "
            "\"descricao\":\"" + prod->getDescricao() + "\", "
            "\"preco\":" + std::to_string(prod->getPreco()) + ", "
            "\"estoque\":" + std::to_string(prod->getQuantidadeEstoque());
            
        // Observação: Caso o produto possua um vendedor agregado, 
        // a lógica de anexar os dados do vendedor iria aqui antes de fechar a chave.
        jsonPayload += "}";

        // Define a URL (Endpoint REST)
        std::string url = this->baseUrl + "/api/produtos"; 
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // Configura o cabeçalho para avisar ao Java que o payload é um JSON
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json; charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        // Anexa o JSON no "corpo" (Body) da requisição POST
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)jsonPayload.length());

        // Executa a requisição
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "[API] Erro ao adicionar produto (POST): " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "[API] Produto enviado com sucesso!" << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

/**
 * @brief Remove um produto do catálogo no servidor remoto. (Verbo HTTP: DELETE)
 * @param id Identificador único do produto a ser deletado.
 */
void ProdutoAPI::deletarProduto(int id) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::cout << "\n[API] Solicitando exclusao do Produto ID: " << id << "..." << std::endl;
        
        // Passagem de Parâmetro por Rota (Path Parameter)
        std::string url = this->baseUrl + "/api/produtos/" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Altera o método padrão (GET) para DELETE explicitamente
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        
        // Configura a captura da resposta (Ex: {"status": 200, "message": "Removido"})
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Executa a requisição
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            std::cerr << "[API] Erro na exclusao (DELETE): " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "--- Resposta do Servidor ---\n" << readBuffer << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }
}

/**
 * @brief Aciona o processamento de uma venda no servidor. (Verbo HTTP: POST)
 * @param produtoId ID do produto vendido.
 * @param qtd Quantidade subtraída do estoque.
 * @param vendedor Agente responsável pela transação (Agregação).
 */
void ProdutoAPI::realizarVenda(int produtoId, int qtd, std::shared_ptr<Vendedor> vendedor) {
    CURL *curl = curl_easy_init();
    if(curl) {
        // Define a URL para a rota específica de vendas
        std::string url = this->baseUrl + "/api/vendas"; 
        
        // [MARSHALLING] - Monta a estrutura de dados (Contexto da Venda) esperada pelo Java
        std::string jsonPayload = "{"
            "\"produto_id\":" + std::to_string(produtoId) + ","
            "\"quantidade\":" + std::to_string(qtd) + ","
            "\"vendedor_id\":\"" + vendedor->id + "\","
            "\"vendedor_nome\":\"" + vendedor->nome + "\""
            "}";

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json; charset=UTF-8");
        
        // Configura os parâmetros do CURL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        // Log local para depuração
        std::cout << "[API] Enviando pedido de venda: " << jsonPayload << std::endl;

        // Captura a resposta do servidor (Pode conter o Resumo da Venda formatado)
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Executa a requisição
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "[API] Falha ao conectar no servidor de vendas." << std::endl;
        } else {
            std::cout << "[API] Resposta do Servidor: " << response << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}