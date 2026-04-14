#ifndef REPLY_H
#define REPLY_H

#include <string>
#include <vector>

class Reply {
private:
    int messageType;
    std::string message;

public:
    static Reply parse(const std::vector<char>& data);

    int getMessageType() const;
    std::string getMessage() const;
};

#endif