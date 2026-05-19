#ifndef PRODUTO_OUTPUT_STREAM_H
#define PRODUTO_OUTPUT_STREAM_H

#include <vector>
#include <memory>
#include <ostream>
#include <string>
#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"
#include "modelos/TipoProduto.h"

class ProdutoOutputStream {
private:
    std::vector<std::shared_ptr<Produto>> produtos;
    int qtd;
    std::ostream& out;

    void writeInt(int value);
    void writeDouble(double value);
    void writeString(const std::string& str);
    void writeProduto(const std::shared_ptr<Produto>& produto);

public:
    ProdutoOutputStream(
        const std::vector<std::shared_ptr<Produto>>& produtos,
        int qtd,
        std::ostream& out);

    void write();
};

#endif // PRODUTO_OUTPUT_STREAM_H
