#ifndef REQUEST_H
#define REQUEST_H

#include <vector>
#include <memory>
#include <cstdint>
#include "modelos/Produto.h"

class Request {
public:
    static std::vector<char> buildAddProdutos(
        const std::vector<std::shared_ptr<Produto>>& produtos);
};

#endif