#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>
#include <vector>

class TcpClient {
private:
    int sock;
    std::string ip;
    int port;

public:
    TcpClient(const std::string& ip, int port);
    ~TcpClient();

    bool connectToServer();
    bool sendData(const std::vector<char>& data);
    std::vector<char> receiveData();
    void closeConnection();
};

#endif // TCP_CLIENT_H