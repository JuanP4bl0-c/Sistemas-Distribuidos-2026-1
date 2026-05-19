#ifndef REPLY_H
#define REPLY_H

#include <cstdint>
#include <string>
#include <vector>

class Reply {
private:
    uint32_t messageType;  // Código da resposta (ex: 200 ou 0)
    std::string message;   // Mensagem interpretada

public:
    Reply(uint32_t type, const std::string& message);

    // Interpreta os dados recebidos do servidor
    static Reply parse(const std::vector<char>& data);

    uint32_t getMessageType() const;
    std::string getMessage() const;
};

#endif // REPLY_H