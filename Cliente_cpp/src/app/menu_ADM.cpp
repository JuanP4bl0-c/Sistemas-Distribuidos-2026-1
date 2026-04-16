#include "modelos/Produto.h"
#include "streams/ProdutoOutPutStream.h"
#include "streams/ProdutoInPutStream.h"

#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

#define port 5001
// #define host "192.168.0.7"
#define host "10.10.231.118"

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

void sendString_toBuffer(std::ostringstream& buffer, const std::string& str);

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
    // 1. Envia o tamanho do pacote (4 bytes para a operação)
    int tamanho = sizeof(int);
    int tamanho_net = htonl(tamanho);
    sendAll(sock, (char*)&tamanho_net, sizeof(int));
    
    // 2. Envia a operação
    int op_net = htonl(operacao);
    sendAll(sock, (char*)&op_net, sizeof(int));
}

int receberResposta(int sock) {
    char resp_buffer[4];
    recvAll(sock, resp_buffer, sizeof(int));
    
    // Debug: mostra os bytes recebidos
    std::cout << "DEBUG - Bytes recebidos: ";
    for(int i = 0; i < 4; i++) {
        std::cout << std::hex << (int)(unsigned char)resp_buffer[i] << " ";
    }
    std::cout << std::dec << std::endl;
    
    int valor = ntohl(*(int*)resp_buffer);
    std::cout << "DEBUG - Valor após ntohl: " << valor << std::endl;
    return valor;
}

// Opção 1: Ver catálogo
void verCatalogo(int sock) {
    std::cout << "\n=== CATÁLOGO DO SERVIDOR ===\n";
    
    // Recebe quantidade
    char qtd_buffer[4];
    recvAll(sock, qtd_buffer, sizeof(int));
    int qtd = ntohl(*(int*)qtd_buffer);  // ✅ Converte de BIG_ENDIAN para host
    
    std::cout << "Total de produtos: " << qtd << "\n";
    
    for (int i = 0; i < qtd; i++) {
        char id_buffer[4], len_buffer[4];
        
        // ID
        recvAll(sock, id_buffer, sizeof(int));
        int id = ntohl(*(int*)id_buffer);  // ✅ Converte
        
        // Nome
        recvAll(sock, len_buffer, sizeof(int));
        int nome_len = ntohl(*(int*)len_buffer);  // ✅ Converte
        char nome_buffer[256];
        recvAll(sock, nome_buffer, nome_len);
        std::string nome(nome_buffer, nome_len);
        
        // Descrição
        recvAll(sock, len_buffer, sizeof(int));
        int desc_len = ntohl(*(int*)len_buffer);  // ✅ Converte
        char desc_buffer[256];
        recvAll(sock, desc_buffer, desc_len);
        std::string descricao(desc_buffer, desc_len);
        
        // Preço
        char preco_buffer_d[8];
        recvAll(sock, preco_buffer_d, sizeof(double));
        // ✅ Converte de BIG_ENDIAN para host
        uint64_t preco_bits = be64toh(*(uint64_t*)preco_buffer_d);
        double preco = *(double*)&preco_bits;

        std::cout << "  [" << id << "] " << nome << " - " << descricao 
                << " - R$ " << preco << "\n";
    }
    std::cout << "============================\n\n";
}

// Opção 2: Adicionar produto com tipo
void adicionarProduto(int sock) {
    std::cout << "\n=== ADICIONAR NOVO PRODUTO ===\n";
    std::cout << "Tipo:\n1. Celular\n2. PowerBank\n3. Capa\n4. Pelicula\nEscolha: ";
    
    int tipo;
    std::cin >> tipo;
    std::cin.ignore();
    
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
    std::cin.ignore();
    
    // Buffer para serializar
    std::ostringstream buffer(std::ios::binary);
    
    // Escreve tipo
    int tipo_net = htonl(tipo);
    buffer.write((char*)&tipo_net, sizeof(int));
    
    // Campos base
    int id_net = htonl(id);
    buffer.write((char*)&id_net, sizeof(int));
    
    sendString_toBuffer(buffer, nome);
    sendString_toBuffer(buffer, descricao);
    
    double preco_net = preco;
    uint64_t preco_bits = htobe64(*(uint64_t*)&preco_net);
    buffer.write((char*)&preco_bits, sizeof(uint64_t));
    
    int estoque_net = htonl(estoque);
    buffer.write((char*)&estoque_net, sizeof(int));
    
    // Campos específicos por tipo
    switch(tipo) {
        case 1: { // Celular
            std::string marca, modelo;
            std::cout << "Marca: ";
            std::getline(std::cin, marca);
            std::cout << "Modelo: ";
            std::getline(std::cin, modelo);
            
            sendString_toBuffer(buffer, marca);
            sendString_toBuffer(buffer, modelo);
            break;
        }
        case 2: { // PowerBank
            std::string marca, modelo;
            int capacidade;
            std::cout << "Marca: ";
            std::getline(std::cin, marca);
            std::cout << "Modelo: ";
            std::getline(std::cin, modelo);
            std::cout << "Capacidade (mAh): ";
            std::cin >> capacidade;
            
            sendString_toBuffer(buffer, marca);
            sendString_toBuffer(buffer, modelo);
            
            int cap_net = htonl(capacidade);
            buffer.write((char*)&cap_net, sizeof(int));
            break;
        }
        case 3:
        case 4: { // Capa ou Película
            std::string modelo, material;
            std::cout << "Modelo: ";
            std::getline(std::cin, modelo);
            std::cout << "Material: ";
            std::getline(std::cin, material);
            
            sendString_toBuffer(buffer, modelo);
            sendString_toBuffer(buffer, material);
            break;
        }
    }
    
    std::string data = buffer.str();
    
    // Envia tamanho
    int tamanho = data.size();
    int tamanho_net = htonl(tamanho);
    sendAll(sock, (char*)&tamanho_net, sizeof(int));
    
    // Envia dados
    sendAll(sock, data.data(), data.size());
    
    std::cout << "Produto adicionado com sucesso!\n\n";
}

// Função auxiliar para serializar string em buffer
void sendString_toBuffer(std::ostringstream& buffer, const std::string& str) {
    int size = str.size();
    int size_net = htonl(size);
    buffer.write((char*)&size_net, sizeof(int));
    buffer.write(str.c_str(), size);
}

// Opção 3: Remover produto
void removerProduto(int sock) {
    std::cout << "\n=== REMOVER PRODUTO ===\n";
    
    int id;
    std::cout << "ID do produto a remover: ";
    std::cin >> id;
    
    int id_net = htonl(id);  // ✅ Converte para BIG_ENDIAN
    sendAll(sock, (char*)&id_net, sizeof(int));
    
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

    for (;;)
    {
        int opcao;
        bool sair = false;
        std::cout << "MENU - ADM \n1.ver catalogo \n2.adicionar Produto\n3.remover Produto\n4.Sair\nEscolha: ";
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
