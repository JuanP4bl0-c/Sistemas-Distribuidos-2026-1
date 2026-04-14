#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"
#include "streams/ProdutoOutPutStream.h"
#include "network/TcpClient.h"
#include "utils/Config.h"

#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

int main() {
    try {
        // 🔹 Carrega configurações
        Config config("config/Config.txt");

        // 🔹 Cria o cliente TCP
        TcpClient client(config.getIp(), config.getPort());

        if (!client.connectToServer()) {
            std::cerr << "Falha ao conectar ao servidor.\n";
            return 1;
        }

        // 🔹 Cria lista polimórfica de produtos
        std::vector<std::shared_ptr<Produto>> lista = {
            std::make_shared<Produto>(
                0, "Carregador", "USB-C", 79.90, 50),

            std::make_shared<Celular>(
                1, "Smartphone", "Android", 1999.90, 20,
                "Samsung", "Galaxy S23"),

            std::make_shared<Capa>(
                3, "Capa Protetora", "Silicone", 29.90, 30,
                "Silicone"),

            std::make_shared<Pelicula>(
                4, "Película", "Vidro Temperado", 19.90, 40,
                "Vidro Temperado"),

            std::make_shared<PowerBank>(
                2, "PowerBank", "Carregador Portátil", 149.90, 15, 10000, "PB-10000", "Xiaomi")
        };

        // 🔹 Serializa os produtos para um buffer binário
        std::ostringstream buffer(std::ios::binary);
        ProdutoOutputStream pos(lista, lista.size(), buffer);
        pos.write();

        std::string serialized = buffer.str();
        std::vector<char> data(serialized.begin(), serialized.end());

        // 🔹 Envia os dados ao servidor
        if (client.sendData(data)) {
            std::cout << "Dados enviados com sucesso ao servidor!\n";
        } else {
            std::cerr << "Erro ao enviar os dados.\n";
        }

        client.closeConnection();
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}