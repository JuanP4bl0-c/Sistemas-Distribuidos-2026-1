#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

#include <cstdint>

enum class MessageType : uint32_t {
    REQUEST_ADD_PRODUTOS = 1,
    REPLY_SUCCESS = 200,
    REPLY_ERROR = 3
};

#endif