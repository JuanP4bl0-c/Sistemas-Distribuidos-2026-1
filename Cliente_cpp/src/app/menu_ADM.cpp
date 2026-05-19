#include "modelos/Produto.h"
#include "streams/ProdutoOutPutStream.h"
#include "streams/ProdutoInPutStream.h"

#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

#define port 5001
#define host "0.0.0.0"

#define OP_PING 0
#define OP_LISTAR 1
#define OP_ADICIONAR 2
#define OP_REMOVER 3

#define RESP_OK 200
#define RESP_ERROR 500
#define RESP_UNAVAILABLE 503


bool sendAll(int sock, const char* data, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t sent = send(sock, data + total, size - total, 0);
        if (sent <= 0) return false;
        total += sent;
    }
    return true;
}

// 🔹 funções auxiliares (tipo OutputStream)
void sendInt(int sock, int value) {
    send(sock, &value, sizeof(int), 0);
}

void sendFloat(int sock, float value) {
    send(sock, &value, sizeof(float), 0);
}

void sendString(int sock, const std::string& str) {
    int size = str.size();
    sendInt(sock, size);
    send(sock, str.c_str(), size, 0);
}

// 🔹 envia um Produto (equivalente ao OutputStream)
void writeProduto(int sock, const Produto& p) {
    sendInt(sock, p.getId());
    sendString(sock, p.getNome());
    sendString(sock, p.getDescricao());
    sendFloat(sock, p.getPreco());
    sendInt(sock, p.getQuantidadeEstoque());
}

// 🔹 envia lista de Produtos (EXIGIDO no trabalho)
void sendProdutos(int sock, const std::vector<Produto>& lista) {
    int qtd = lista.size();
    sendInt(sock, qtd);

    for (const auto& p : lista) {
        writeProduto(sock, p);
    }
}

bool recvAll(int sock, char* buffer, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t received = recv(sock, buffer + total, size - total, 0);
        if (received <= 0) return false;
        total += received;
    }
    return true;
}


// Envia operação ao servidor
void enviarOperacao(int sock, int operacao) {
    sendInt(sock, operacao);
}

// Recebe resposta do servidor
int receberResposta(int sock) {
    char resp_buffer[4];
    recvAll(sock, resp_buffer, sizeof(int));
    return *(int*)resp_buffer;
}

// Opção 1: Ver catálogo
void verCatalogo(int sock) {
    std::cout << "\n=== CATÁLOGO DO SERVIDOR ===\n";
    
    // Recebe quantidade
    char qtd_buffer[4];
    recvAll(sock, qtd_buffer, sizeof(int));
    int qtd = *(int*)qtd_buffer;
    
    std::cout << "Total de produtos: " << qtd << "\n";
    
    for (int i = 0; i < qtd; i++) {
        char id_buffer[4], len_buffer[4], preco_buffer[8];
        
        // ID
        recvAll(sock, id_buffer, sizeof(int));
        int id = *(int*)id_buffer;
        
        // Nome
        recvAll(sock, len_buffer, sizeof(int));
        int nome_len = *(int*)len_buffer;
        char nome_buffer[256];
        recvAll(sock, nome_buffer, nome_len);
        std::string nome(nome_buffer, nome_len);
        
        // Descrição
        recvAll(sock, len_buffer, sizeof(int));
        int desc_len = *(int*)len_buffer;
        char desc_buffer[256];
        recvAll(sock, desc_buffer, desc_len);
        std::string descricao(desc_buffer, desc_len);
        
        // Preço
        char preco_buffer_d[8];
        recvAll(sock, preco_buffer_d, sizeof(double));
        double preco = *(double*)preco_buffer_d;
        
        std::cout << "  [" << id << "] " << nome << " - " << descricao 
                  << " - R$ " << preco << "\n";
    }
    std::cout << "============================\n\n";
}

// Opção 2: Adicionar produto
void adicionarProduto(int sock) {
    std::cout << "\n=== ADICIONAR NOVO PRODUTO ===\n";
    
    int id;
    std::string nome, descricao;
    double preco;
    int estoque;
    
    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();
    
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    
    std::cout << "Descrição: ";
    std::getline(std::cin, descricao);
    
    std::cout << "Preço: ";
    std::cin >> preco;
    
    std::cout << "Estoque: ";
    std::cin >> estoque;
    
    // Cria produto
    Produto p(id, nome, descricao, preco, estoque);
    std::vector<Produto> lista = {p};
    
    // Serializa
    std::ostringstream buffer(std::ios::binary);
    ProdutoOutputStream pos(lista, 1, buffer);
    pos.write();
    
    std::string data = buffer.str();
    
    // Envia tamanho (BIG_ENDIAN para compatibilidade)
    int tamanho = data.size();
    int tamanho_net = htonl(tamanho);
    sendAll(sock, (char*)&tamanho_net, sizeof(int));
    
    // Envia dados
    sendAll(sock, data.data(), data.size());
    
    std::cout << "Produto adicionado com sucesso!\n\n";
}

// Opção 3: Remover produto
void removerProduto(int sock) {
    std::cout << "\n=== REMOVER PRODUTO ===\n";
    
    int id;
    std::cout << "ID do produto a remover: ";
    std::cin >> id;
    
    sendInt(sock, id);
    
    std::cout << "Produto removido com sucesso!\n\n";
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Erro ao conectar\n";
        return 1;
    }
    
    std::cout << "Servidor conectado!\n";

    int operacao_net;
    for (;;)
    {
        int opcao;
        bool sair = false;
        std::cout << "MENU\n1.ver catalogo \n2.adicionar Celular\n3.remover Produto\n4.Sair\nEscolha: ";
        std::cin >> opcao;

        switch (opcao)
        {
        case 1:{

            
            enviarOperacao(sock, OP_LISTAR);
            std::cout << "Request enviada. Aguardando servidor..." << std::endl;
            
            int resp = receberResposta(sock);
            std::cout << "Resposta recebida: " << resp << std::endl;
            if (resp == RESP_OK) {
                verCatalogo(sock);
            } else {
                std::cout << "Erro ao listar catálogo\n\n";
            }
            continue;
        }
        
        case 2:{
            
            // ADICIONAR PRODUTO
            enviarOperacao(sock, OP_ADICIONAR);
            
            int resp = receberResposta(sock);
            if (resp == RESP_OK) {
                adicionarProduto(sock);
            } else {
                std::cout << "Erro ao adicionar produto\n\n";
            }
            
            continue;
        }
        case 3:{

            // REMOVER PRODUTO
            enviarOperacao(sock, OP_REMOVER);
            
            int resp = receberResposta(sock);
            if (resp == RESP_OK) {
                removerProduto(sock);
            } else {
                std::cout << "Erro ao remover produto\n\n";
            }
            continue;
        }
        case 4:{
            
            /* code */
            sair = true;
            break;
        }
            
        
        default:
        std::cout << "Comando invalido, tente novamente\n";
        }

        if (sair)
        {
            break;
        }
        
    }
    



    close(sock);
    return 0;
}
