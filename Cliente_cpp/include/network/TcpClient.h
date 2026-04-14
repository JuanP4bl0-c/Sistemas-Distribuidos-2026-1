#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>
#include <vector>
#include <cstddef>

class TcpClient {
private:
    int sock;
    std::string ip;
    int port;

    // Envia todos os bytes garantindo que nada seja perdido
    bool sendAll(const char* data, size_t size);

public:
    TcpClient(const std::string& ip, int port);
    ~TcpClient();

    // Conecta ao servidor
    bool connectToServer();

    // Envia dados precedidos pelo tamanho do pacote
    bool sendData(const std::vector<char>& data);

    // Fecha a conexão
    void closeConnection();
    
    std::vector<char> receiveData();
};

#endif // TCP_CLIENT_H