#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

#include <cstdint>

enum class MessageType : uint32_t {
    LISTAR = 1,
    ADICIONAR = 2,
    REMOVER = 3,
    REPLY_SUCCESS = 200,
    REPLY_ERROR = 0
};

#endif