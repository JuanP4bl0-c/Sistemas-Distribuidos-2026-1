#include "network/TcpClient.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

TcpClient::TcpClient(const std::string& ip, int port)
    : ip(ip), port(port), sock(-1) {}

TcpClient::~TcpClient() {
    closeConnection();
}

void TcpClient::connectToServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        throw std::runtime_error("Erro ao criar socket.");

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &server.sin_addr) <= 0)
        throw std::runtime_error("Endereço IP inválido.");

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0)
        throw std::runtime_error("Erro ao conectar ao servidor.");
}

bool TcpClient::sendAll(const char* data, size_t size) {
    size_t total = 0;
    while (total < size) {
        ssize_t sent = send(sock, data + total, size - total, 0);
        if (sent <= 0)
            return false;
        total += sent;
    }
    return true;
}

void TcpClient::sendPacket(const std::string& data) {
    // 🔹 Envia o tamanho do pacote em big-endian
    uint32_t tamanho = htonl(static_cast<uint32_t>(data.size()));

    if (!sendAll(reinterpret_cast<char*>(&tamanho), sizeof(tamanho)))
        throw std::runtime_error("Erro ao enviar o tamanho do pacote.");

    // 🔹 Envia os dados
    if (!sendAll(data.data(), data.size()))
        throw std::runtime_error("Erro ao enviar os dados.");
}

void TcpClient::closeConnection() {
    if (sock >= 0) {
        close(sock);
        sock = -1;
    }
}