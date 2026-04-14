#include "protocols/Request.h"
#include "protocols/MessageType.h"
#include "streams/ProdutoOutPutStream.h"
#include <sstream>
#include <arpa/inet.h>

std::vector<char> Request::buildAddProdutos(
    const std::vector<std::shared_ptr<Produto>>& produtos) {

    std::ostringstream buffer(std::ios::binary);

    // Tipo da mensagem
    uint32_t type = htonl(
        static_cast<uint32_t>(MessageType::REQUEST_ADD_PRODUTOS));
    buffer.write(reinterpret_cast<char*>(&type), sizeof(type));

    // Serialização dos produtos
    ProdutoOutputStream pos(produtos, produtos.size(), buffer);
    pos.write();

    std::string data = buffer.str();
    return std::vector<char>(data.begin(), data.end());
}