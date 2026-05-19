#include "network/TcpClient.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

TcpClient::TcpClient(const std::string& ip, int port)
    : sock(-1), ip(ip), port(port) {}

TcpClient::~TcpClient() {
    closeConnection();
}

bool TcpClient::connectToServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Erro ao criar o socket.\n";
        return false;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &server.sin_addr) <= 0) {
        std::cerr << "Endereço IP inválido.\n";
        return false;
    }

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Erro ao conectar ao servidor.\n";
        return false;
    }

    std::cout << "Conectado ao servidor " << ip << ":" << port << std::endl;
    return true;
}

bool TcpClient::sendData(const std::vector<char>& data) {
    size_t totalSent = 0;

    while (totalSent < data.size()) {
        ssize_t sent = send(sock,
                            data.data() + totalSent,
                            data.size() - totalSent,
                            0);
        if (sent <= 0) {
            std::cerr << "Erro ao enviar dados.\n";
            return false;
        }
        totalSent += sent;
    }

    return true;
}

std::vector<char> TcpClient::receiveData() {
    uint32_t netCode;
    size_t totalReceived = 0;

    while (totalReceived < sizeof(netCode)) {
        ssize_t received = recv(sock,
                                reinterpret_cast<char*>(&netCode) + totalReceived,
                                sizeof(netCode) - totalReceived,
                                0);
        if (received <= 0) {
            perror("Erro ao receber resposta");
            return {};
        }
        totalReceived += received;
    }

    std::vector<char> data(sizeof(netCode));
    std::memcpy(data.data(), &netCode, sizeof(netCode));

    return data;
}

void TcpClient::closeConnection() {
    if (sock >= 0) {
        close(sock);
        sock = -1;
    }
}