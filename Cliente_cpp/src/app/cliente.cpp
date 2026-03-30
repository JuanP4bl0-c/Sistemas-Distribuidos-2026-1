#include "modelos/Produto.h"

#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

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

    if (sock < 0) {
        std::cerr << "Erro ao criar socket\n";
        return 1;
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("192.168.0.6");

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Erro ao conectar\n";
        return 1;
    }

    // 🔹 criando lista de produtos (array)
    std::vector<Produto> lista = {
        Produto(1, "Carregador", "USB-C", 79.90, 50),
        Produto(2, "Capa", "Silicone", 29.90, 30)
    };

    // 🔹 envia tudo (igual OutputStream)
    sendProdutos(sock, lista);

    std::cout << "Dados enviados com sucesso!\n";

    close(sock);
    return 0;
}