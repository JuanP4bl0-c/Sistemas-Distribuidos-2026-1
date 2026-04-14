#ifndef PRODUTO_INPUT_STREAM_H
#define PRODUTO_INPUT_STREAM_H

#include <istream>
#include <vector>
#include <memory>
#include <string>

#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"
#include "modelos/TipoProduto.h"

class ProdutoInputStream {
private:
    std::istream& in;

    int readInt();
    double readDouble();
    std::string readString();

public:
    explicit ProdutoInputStream(std::istream& in);

    // Retorna uma lista polimórfica
    std::vector<std::shared_ptr<Produto>> read();
};

#endif // PRODUTO_INPUT_STREAM_H