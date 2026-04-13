#ifndef PRODUTO_OUTPUT_STREAM_H
#define PRODUTO_OUTPUT_STREAM_H

#include <vector>
#include <ostream>
#include "modelos/Produto.h"

class ProdutoOutputStream {
private:
    std::vector<Produto> produtos;
    int qtd;
    std::ostream& out;

    // Métodos auxiliares para escrita em big-endian
    void writeInt(int value);
    void writeDouble(double value);
    void writeString(const std::string& str);

public:
    ProdutoOutputStream(const std::vector<Produto>& produtos,
                        int qtd,
                        std::ostream& out);

    void write();
};

#endif // PRODUTO_OUTPUT_STREAM_H