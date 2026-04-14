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
        Config config("config/Config.txt");

        TcpClient client(config.getIp(), config.getPort());

        if (!client.connectToServer()) {
            std::cerr << "Falha ao conectar ao servidor.\n";
            return 1;
        }

        std::vector<std::shared_ptr<Produto>> lista = {
            // Produto Base: ID, Nome, Descrição, Preço, Estoque
            std::make_shared<Produto>(
                0, "Carregador", "USB-C Fast Charge", 79.90, 50),

            // Celular: Base + Marca, Modelo
            std::make_shared<Celular>(
                1, "Smartphone", "Android 14", 1999.90, 20,
                "Samsung", "Galaxy S23"),

            // Capa: Base + Modelo do Celular, Material (Ordem do Java!)
            std::make_shared<Capa>(
                2, "Capa Protetora", "Capa Anti-Impacto", 29.90, 30,
                "Galaxy S23", "Silicone"),

            // Pelicula: Base + Modelo do Celular, Tipo/Material (Ordem do Java!)
            std::make_shared<Pelicula>(
                3, "Película", "Proteção de Tela", 19.90, 40,
                "Galaxy S23", "Vidro Temperado"),

            // PowerBank: Base + Marca, Modelo, Capacidade (Ordem do Java!)
            std::make_shared<PowerBank>(
                4, "PowerBank", "Carregador Portátil", 149.90, 15,
                "Xiaomi", "PB-10000", 10000)
        };

        auto requestData = Request::buildAddProdutos(lista);

        // Envia a requisição
        if (!client.sendData(requestData)) {
            std::cerr << "Erro ao enviar a requisicao.\n";
            return 1;
        }

        // Recebe a resposta
        std::vector<char> replyData = client.receiveData();

        if (replyData.empty()) {
            std::cerr << "Erro ao receber resposta do servidor.\n";
            return 1;
        }

        // Interpreta a resposta
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