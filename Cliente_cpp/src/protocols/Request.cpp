#include "protocols/Request.h"
#include "protocols/MessageType.h"
#include "streams/ProdutoOutPutStream.h"

#include <sstream>
#include <arpa/inet.h>  // htonl
#include <cstring>

std::vector<char> Request::buildAddProdutos(
    const std::vector<std::shared_ptr<Produto>>& produtos) {

    // 🔹 Buffer para o corpo da mensagem
    std::ostringstream payload(std::ios::binary);

    // 1. Tipo da operação (ADICIONAR = 2)
    uint32_t type = htonl(
        static_cast<uint32_t>(MessageType::ADICIONAR));
    payload.write(reinterpret_cast<char*>(&type), sizeof(type));

    // 2. Serialização dos produtos
    ProdutoOutputStream pos(produtos, produtos.size(), payload);
    pos.write();

    // 🔹 Converte o payload para string
    std::string body = payload.str();

    // 3. Tamanho do payload (em big-endian)
    uint32_t size = htonl(static_cast<uint32_t>(body.size()));

    // 4. Monta o pacote final: [tamanho][payload]
    std::vector<char> packet(sizeof(uint32_t) + body.size());
    std::memcpy(packet.data(), &size, sizeof(uint32_t));
    std::memcpy(packet.data() + sizeof(uint32_t),
                body.data(),
                body.size());

    return packet;
}