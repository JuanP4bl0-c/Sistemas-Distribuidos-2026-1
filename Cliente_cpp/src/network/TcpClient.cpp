#include "network/TcpClient.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

TcpClient::TcpClient(const std::string& ip, int port)
    : sock(-1), ip(ip), port(port) {}

TcpClient::~TcpClient() {
    closeConnection();
}

// 🔹 Conecta ao servidor
bool TcpClient::connectToServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Erro ao criar socket.\n";
        return false;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &server.sin_addr) <= 0) {
        std::cerr << "IP inválido.\n";
        return false;
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&server), sizeof(server)) < 0) {
        std::cerr << "Erro ao conectar ao servidor.\n";
        close(sock);
        sock = -1;
        return false;
    }

    std::cout << "Conectado ao servidor " << ip << ":" << port << std::endl;
    return true;
}

// 🔹 Envia todos os bytes
bool TcpClient::sendAll(const char* data, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t sent = send(sock, data + total, size - total, 0);
        if (sent <= 0) {
            std::cerr << "Erro ao enviar dados.\n";
            return false;
        }
        total += sent;
    }
    return true;
}

// 🔹 Envia dados com o tamanho do pacote em big-endian
bool TcpClient::sendData(const std::vector<char>& data) {
    if (sock < 0) {
        std::cerr << "Socket não conectado.\n";
        return false;
    }

    uint32_t size = htonl(static_cast<uint32_t>(data.size()));

    // Envia o tamanho do pacote
    if (!sendAll(reinterpret_cast<const char*>(&size), sizeof(size)))
        return false;

    // Envia o conteúdo
    return sendAll(data.data(), data.size());
}

// 🔹 Fecha a conexão
void TcpClient::closeConnection() {
    if (sock >= 0) {
        close(sock);
        sock = -1;
    }
}