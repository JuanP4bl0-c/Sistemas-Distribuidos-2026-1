#include "utils/Config.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

<<<<<<< HEAD
// Lê arquivo de configuração no formato KEY=VALUE (ex: IP=127.0.0.1, PORT=8080)
Config::Config(const std::string& filename) : port(0) {
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Não foi possível abrir o arquivo de configuração: " + filename);
=======
Config::Config(const std::string& filename) : port(0) {
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Não foi possível abrir o arquivo de configuração.");
>>>>>>> Entrega_2_Invocacao_Remota

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "IP")
                ip = value;
            else if (key == "PORT")
                port = std::stoi(value);
        }
    }

    if (ip.empty() || port == 0)
        throw std::runtime_error("Configuração inválida no arquivo.");
}

std::string Config::getIp() const {
    return ip;
}

int Config::getPort() const {
    return port;
}