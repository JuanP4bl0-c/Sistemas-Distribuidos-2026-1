#include <arpa/inet.h>
#include <unistd.h>
#include <endian.h>
#include <iostream>
#include <string>
#include <cstring>

#define host "10.10.231.118"
#define port 5001

bool recvAll(int sock, char* buffer, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t received = recv(sock, buffer + total, size - total, 0);
        if (received <= 0) return false;
        total += received;
    }
    return true;
}

bool sendAll(int sock, const char* data, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t sent = send(sock, data + total, size - total, 0);
        if (sent <= 0) return false;
        total += sent;
    }
    return true;
}

int main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in a{};
    a.sin_family = AF_INET;
    a.sin_port = htons(port);
    inet_pton(AF_INET, host, &a.sin_addr);
    
    if (connect(s, (sockaddr*)&a, sizeof(a)) < 0) {
        std::cerr << "Erro ao conectar\n";
        return 1;
    }
    
    std::cout << "Conectado ao servidor!\n\n";
    
    int operacao = htonl(1); // OP_LISTAR
    sendAll(s, (char*)&operacao, sizeof(int));
    
    std::cout << "Requisição enviada. Aguardando resposta...\n";
    
    // ✅ Recebe quantidade de produtos PRIMEIRO
    char qtd_buffer[4];
    recvAll(s, qtd_buffer, sizeof(int));
    int quantidade = ntohl(*(int*)qtd_buffer);
    
    std::cout << "\n=== CATÁLOGO (" << quantidade << " produtos) ===\n\n";
    
    // ✅ Recebe cada produto
    for (int i = 0; i < quantidade; i++) {
        // ID
        char id_buffer[4];
        recvAll(s, id_buffer, sizeof(int));
        int id = ntohl(*(int*)id_buffer);
        
        // Nome
        char len_buffer[4];
        recvAll(s, len_buffer, sizeof(int));
        int nome_len = ntohl(*(int*)len_buffer);
        std::string nome(nome_len, 0);
        recvAll(s, (char*)&nome[0], nome_len);
        
        // Descrição
        recvAll(s, len_buffer, sizeof(int));
        int desc_len = ntohl(*(int*)len_buffer);
        std::string descricao(desc_len, 0);
        recvAll(s, (char*)&descricao[0], desc_len);
        
        // Preço
        char preco_buffer[8];
        recvAll(s, preco_buffer, sizeof(double));
        uint64_t preco_bits = be64toh(*(uint64_t*)preco_buffer);
        double preco = *(double*)&preco_bits;
        
        std::cout << "[" << id << "] " << nome << " - " << descricao 
                  << " - R$ " << preco << "\n";
    }
    
    // ✅ Agora recebe a resposta (200)
    char resp_buffer[4];
    recvAll(s, resp_buffer, sizeof(int));
    int resposta = ntohl(*(int*)resp_buffer);
    
    std::cout << "\nResposta do servidor: " << resposta << "\n";
    std::cout << "=============================\n";
    close(s);
    return 0;
}