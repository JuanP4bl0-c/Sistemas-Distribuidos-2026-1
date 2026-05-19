#include "streams/ProdutoOutPutStream.h"
#include "streams/ProdutoInputStream.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"

#include <sstream>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    try {
        // 🔹 Lista de produtos
        std::vector<std::shared_ptr<Produto>> produtos = {
            std::make_shared<Celular>(
                1, "Smartphone", "Android", 1999.90, 20,
                "Samsung", "Galaxy S23"),

            std::make_shared<Capa>(
                2, "Capa", "Silicone", 29.90, 30,
                "Silicone", "Galaxy S23"),

            std::make_shared<Pelicula>(
                3, "Película", "Vidro", 19.90, 40,
                "Galaxy S23", "Vidro Temperado"),

            std::make_shared<PowerBank>(
                4, "PowerBank", "Portátil", 149.90, 15,
                "Xiaomi", "PB-10000", 10000)

        };

        // 🔹 Serialização
        std::stringstream buffer(std::ios::in | std::ios::out | std::ios::binary);
        ProdutoOutputStream pos(produtos, produtos.size(), buffer);
        pos.write();

        // 🔹 Desserialização
        ProdutoInputStream pis(buffer);
        auto produtosLidos = pis.read();

        // 🔹 Exibição
        std::cout << "Produtos desserializados:\n";
        for (const auto& p : produtosLidos) {
            p->mostrar();
        }

        std::cout << "\n✅ Teste concluído com sucesso!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "❌ Erro durante o teste: " << e.what() << std::endl;
    }

    return 0;
}