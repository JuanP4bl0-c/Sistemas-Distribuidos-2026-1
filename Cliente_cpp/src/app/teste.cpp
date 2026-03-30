#include <vector>
#include <fstream>
#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "streams/ProdutoOutPutStream.h"

int main() {

    Celular c(3, "Celular", "Smartphone", 999.9, 5, "Samsung", "Galaxy S21");

    std::vector<Produto> lista = {
        Produto(1, "Carregador", "USB-C", 79.9, 10),
        Produto(2, "Capa", "Silicone", 29.9, 20),
        c
    };

    std::ofstream file("dados.bin", std::ios::binary);

    ProdutoOutputStream pos(lista, lista.size(), file);
    pos.write();

    file.close();

    return 0;
}