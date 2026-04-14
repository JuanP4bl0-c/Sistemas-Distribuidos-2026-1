#include "modelos/Produto.h"
#include "streams/ProdutoOutPutStream.h"
#include "network/TcpClient.h"
#include "utils/Config.h"

#include <iostream>
#include <vector>
#include <sstream>

int main() {
    try {
        // 🔹 1. Ler configurações
        Config config("config/client.conf");
        std::string ip = config.getIp();
        int port = config.getPort();

        // 🔹 2. Criar lista de produtos
        std::vector<Produto> lista = {
            Produto(1, "Carregador", "USB-C", 79.90, 50),
            Produto(2, "Capa", "Silicone", 29.90, 30)
        };

        // 🔹 3. Serializar os dados
        std::ostringstream buffer(std::ios::binary);
        ProdutoOutputStream pos(lista, lista.size(), buffer);
        pos.write();
        std::string data = buffer.str();

        // 🔹 4. Enviar via TCP
        TcpClient client(ip, port);
        client.connectToServer();
        client.sendPacket(data);

        std::cout << "Pacote enviado com sucesso!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}