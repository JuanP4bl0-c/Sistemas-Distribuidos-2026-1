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

    std::vector<Produto> lista = {
        Produto(1, "Carregador", "USB-C", 79.90, 50),
        Produto(2, "Capa", "Silicone", 29.90, 30)
    };

    //  gera binário
    std::ostringstream buffer(std::ios::binary);
    ProdutoOutputStream pos(lista, lista.size(), buffer);
    pos.write();

    std::string data = buffer.str();

    // envia tamanho do pacote
    int tamanho = data.size();
    int tamanho_net = htonl(tamanho); // importante pro Java
    sendAll(sock, (char*)&tamanho_net, sizeof(int));

    //  envia dados
    sendAll(sock, data.data(), data.size());

    std::cout << "Pacote enviado com sucesso!\n";

    std::cout << "Aguardando resposta do servidor...\n";

    // Lê quantidade em LITTLE_ENDIAN
    int qtd_recebida = 0;
    char qtd_buffer[4];
    recvAll(sock, qtd_buffer, sizeof(int));
    qtd_recebida = *(int*)qtd_buffer;  // LE nativo
    
    std::cout << "O servidor me enviou " << qtd_recebida << " produtos do catalogo atualizado!\n";

    for (int i = 0; i < qtd_recebida; i++) {
        char id_buffer[4], len_buffer[4], preco_buffer[8];
        
        // Lê ID em LITTLE_ENDIAN
        recvAll(sock, id_buffer, sizeof(int));
        int id = *(int*)id_buffer;
        
        // Lê nome (tamanho em LITTLE_ENDIAN + string)
        recvAll(sock, len_buffer, sizeof(int));
        int nome_len = *(int*)len_buffer;
        char nome_buffer[256];
        recvAll(sock, nome_buffer, nome_len);
        std::string nome(nome_buffer, nome_len);
        
        // Lê descrição (tamanho em LITTLE_ENDIAN + string)
        recvAll(sock, len_buffer, sizeof(int));
        int desc_len = *(int*)len_buffer;
        char desc_buffer[256];
        recvAll(sock, desc_buffer, desc_len);
        std::string descricao(desc_buffer, desc_len);
        
        // Lê preço em LITTLE_ENDIAN (8 bytes double)
        recvAll(sock, preco_buffer, sizeof(double));
        double preco = *(double*)preco_buffer;
        
        std::cout << "  Produto " << (i+1) << ": " << nome << " - R$ " << preco << "\n";
    }


    close(sock);
    return 0;
}
