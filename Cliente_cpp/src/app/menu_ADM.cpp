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
    
    std::cout << "Servidor conectado!\n";
    for (;;)
    {
        int opcao;
        bool sair = false;
        std::cout << "MENU\n1.ver catalogo \n2.adicionar Produto\n3.remover Produto\n4.Sair\nEscolha: ";
        std::cin >> opcao;
        switch (opcao)
        {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            sair = true;
            break;
        
        
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
