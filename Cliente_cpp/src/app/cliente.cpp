#include "modelos/Produto.h"
#include "streams/ProdutoOutPutStream.h"

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

    close(sock);
    return 0;
}
