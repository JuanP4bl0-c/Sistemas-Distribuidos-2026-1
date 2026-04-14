#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>

class TcpClient {
private:
    std::string ip;
    int port;
    int sock;

    bool sendAll(const char* data, size_t size);

public:
    TcpClient(const std::string& ip, int port);
    ~TcpClient();

    void connectToServer();
    void sendPacket(const std::string& data);
    void closeConnection();
};

#endif // TCP_CLIENT_H