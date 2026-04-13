#include "modelos/Produto.h"
#include "streams/ProdutoOutPutStream.h"

#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

bool sendAll(int sock, const char* data, size_t size);

bool sendAll(int sock, const char* data, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t sent = send(sock, data + total, size - total, 0);
        if (sent <= 0) return false;
        total += sent;
    }
    return true;
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5001);
    server.sin_addr.s_addr = inet_addr("10.10.247.4");

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Erro ao conectar\n";
        return 1;
    }

    std::vector<Produto> lista = {
        Produto(1, "Carregador", "USB-C", 79.90, 50),
        Produto(2, "Capa", "Silicone", 29.90, 30)
    };

    // gera binário
    std::ostringstream buffer(std::ios::binary);
    ProdutoOutputStream pos(lista, lista.size(), buffer);
    pos.write();

    std::string data = buffer.str();

    //  envia tamanho do pacote
    int tamanho = data.size();
    int tamanho_net = htonl(tamanho); // importante pro Java
    sendAll(sock, (char*)&tamanho_net, sizeof(int));

    // envia dados
    sendAll(sock, data.data(), data.size());

    std::cout << "Pacote enviado com sucesso!\n";

    close(sock);
    return 0;
}