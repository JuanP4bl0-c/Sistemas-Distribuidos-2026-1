#include "network/TcpClient.h"
#include "protocols/Request.h"
#include "protocols/Reply.h"
#include "utils/Config.h"
#include "modelos/Produto.h"
#include <memory>
#include <vector>
#include <iostream>

int main() {
    Config config("config/Config.txt");
    TcpClient client(config.getIp(), config.getPort());

    if (!client.connectToServer()) {
        std::cerr << "Erro ao conectar.\n";
        return 1;
    }

    std::vector<std::shared_ptr<Produto>> produtos = {
        std::make_shared<Produto>(
            0, "Carregador", "USB-C", 79.90, 50)
    };

    // 🔹 Envia request
    auto request = Request::buildAddProdutos(produtos);
    client.sendData(request);

    // 🔹 Recebe reply
    auto replyData = client.receiveData();
    Reply reply = Reply::parse(replyData);

    if (reply.getMessageType() == 2)
        std::cout << "Sucesso: " << reply.getMessage() << std::endl;
    else
        std::cout << "Erro: " << reply.getMessage() << std::endl;

    client.closeConnection();
    return 0;
}