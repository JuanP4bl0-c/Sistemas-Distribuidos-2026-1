#ifndef PRODUTO_INPUT_STREAM_H
#define PRODUTO_INPUT_STREAM_H

#include <vector>
#include <istream>
#include "modelos/Produto.h"

class ProdutoInputStream {
private:
    std::istream& in;
    std::vector<Produto> produtos;

    int readInt();
    double readDouble();
    std::string readString();

public:
    explicit ProdutoInputStream(std::istream& in);

    std::vector<Produto> read();   // Lê todos os produtos
};

#endif