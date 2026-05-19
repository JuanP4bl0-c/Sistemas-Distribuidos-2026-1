#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
private:
    std::string ip;
    int port;

public:
    explicit Config(const std::string& filename);

    std::string getIp() const;
    int getPort() const;
};

#endif // CONFIG_H