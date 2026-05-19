#include "protocols/Reply.h"
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

Reply::Reply(uint32_t type, const std::string& message)
    : messageType(type), message(message) {}

Reply Reply::parse(const std::vector<char>& data) {
    if (data.size() < sizeof(uint32_t)) {
        throw std::runtime_error("Resposta inválida: dados insuficientes.");
    }

    uint32_t netCode;
    std::memcpy(&netCode, data.data(), sizeof(uint32_t));
    uint32_t code = ntohl(netCode);

    std::string msg;
    switch (code) {
        case 200:
            msg = "Operação realizada com sucesso.";
            break;
        case 0:
            msg = "Erro na operação.";
            break;
        default:
            msg = "Código desconhecido: " + std::to_string(code);
            break;
    }

    return Reply(code, msg);
}

uint32_t Reply::getMessageType() const {
    return messageType;
}

std::string Reply::getMessage() const {
    return message;
}