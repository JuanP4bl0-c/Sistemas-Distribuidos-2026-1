#include <vector>
#include <memory>
#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/PowerBank.h"
#include "modelos/Pelicula.h"
#include "modelos/TipoProduto.h"

int main() {
    std::vector<std::shared_ptr<Produto>> produtos;

    produtos.push_back(std::make_shared<Produto>(
        1, "Carregador", "USB-C", 79.90, 50));

    produtos.push_back(std::make_shared<Celular>(
        2, "Smartphone", "Android", 1999.90, 20, "Samsung", "Galaxy S23"));

    produtos.push_back(std::make_shared<Capa>(
        3, "Capa Protetora", "Silicone", 29.90, 30, "Silicone"));

    produtos.push_back(std::make_shared<PowerBank>(
        5, "PowerBank", "Portátil", 199.90, 10, 10000, "PB-1000", "MarcaX"));

    produtos.push_back(std::make_shared<Pelicula>(
        4, "Película de Vidro", "Proteção para tela", 49.90, 25, "Vidro Temperado"));

    for (const auto& p : produtos) {
        p->mostrar();
    }

    return 0;
}