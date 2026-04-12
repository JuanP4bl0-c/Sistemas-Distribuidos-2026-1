#ifndef PRODUTO_INPUT_STREAM_H
#define PRODUTO_INPUT_STREAM_H

#include <vector>
#include <istream>
#include "modelos/Produto.h"

class ProdutoInputStream {

    private:
        std::istream& entrada;

    public:
    
        ProdutoInputStream(std::istream& entrada);
        int readInt();
        float readFloat();
        double readDouble();
        std::string readString();
        Produto readProduto();

};

#endif