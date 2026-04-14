#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"
#include "protocols/Request.h"
#include "protocols/Reply.h"
#include "protocols/MessageType.h"
#include "network/TcpClient.h"
#include "utils/Config.h"

#include <iostream>
#include <vector>
#include <memory>

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
                2, "PowerBank", "Carregador Portátil", 149.90, 15,
                10000, "PB-10000", "Xiaomi")
        };

        // 🔹 Cria a requisição
        std::vector<char> requestData =
            Request::buildAddProdutos(lista);

        // 🔹 Envia a requisição
        if (!client.sendData(requestData)) {
            std::cerr << "Erro ao enviar a requisição.\n";
            return 1;
        }

        std::cout << "Requisição enviada com sucesso!\n";

        // 🔹 Recebe a resposta do servidor
        std::vector<char> replyData = client.receiveData();

        if (replyData.empty()) {
            std::cerr << "Erro ao receber resposta do servidor.\n";
            return 1;
        }

        // 🔹 Interpreta a resposta
        Reply reply = Reply::parse(replyData);

        if (reply.getMessageType() ==
            static_cast<uint32_t>(MessageType::REPLY_SUCCESS)) {
            std::cout << "Servidor: " << reply.getMessage() << std::endl;
        } else {
            std::cerr << "Erro do servidor: "
                      << reply.getMessage() << std::endl;
        }

        client.closeConnection();
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}