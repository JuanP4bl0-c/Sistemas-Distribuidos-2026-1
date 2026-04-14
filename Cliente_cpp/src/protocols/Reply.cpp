#include "protocols/Reply.h"
#include "protocols/MessageType.h"
#include <sstream>
#include <arpa/inet.h>

Reply Reply::parse(const std::vector<char>& data) {
    std::istringstream stream(
        std::string(data.begin(), data.end()), std::ios::binary);

    uint32_t typeNet;
    stream.read(reinterpret_cast<char*>(&typeNet), sizeof(typeNet));
    uint32_t type = ntohl(typeNet);

    uint32_t sizeNet;
    stream.read(reinterpret_cast<char*>(&sizeNet), sizeof(sizeNet));
    uint32_t size = ntohl(sizeNet);

    std::string message(size, '\0');
    stream.read(&message[0], size);

    Reply reply;
    reply.messageType = static_cast<int>(type);
    reply.message = message;
    return reply;
}

int Reply::getMessageType() const {
    return messageType;
}

std::string Reply::getMessage() const {
    return message;
}