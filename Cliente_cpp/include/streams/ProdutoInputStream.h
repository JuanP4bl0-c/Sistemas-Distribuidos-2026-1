#ifndef PRODUTO_INPUT_STREAM_H
#define PRODUTO_INPUT_STREAM_H

#include <vector>
#include <istream>
#include <string>
#include "modelos/Produto.h"

class ProdutoInputStream {
private:
    std::istream& in;

    // Métodos auxiliares para leitura em big-endian
    int readInt();
    double readDouble();
    std::string readString();

public:
    explicit ProdutoInputStream(std::istream& in);

    // Lê todos os produtos do stream
    std::vector<Produto> read();
};

#endif // PRODUTO_INPUT_STREAM_H