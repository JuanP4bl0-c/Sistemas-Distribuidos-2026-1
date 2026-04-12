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

public:
    ProdutoOutputStream(const std::vector<Produto>& produtos, int qtd, std::ostream& out);

    void write();
};

#endif