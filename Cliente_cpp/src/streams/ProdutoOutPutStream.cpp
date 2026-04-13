#include "streams/ProdutoOutPutStream.h"
#include <arpa/inet.h>   // htonl
#include <cstring>
#include <cstdint>

// Construtor
ProdutoOutputStream::ProdutoOutputStream(
    const std::vector<Produto>& produtos,
    int qtd,
    std::ostream& out)
    : produtos(produtos), qtd(qtd), out(out) {}

// Escreve inteiro em big-endian
void ProdutoOutputStream::writeInt(int value) {
    uint32_t net = htonl(static_cast<uint32_t>(value));
    out.write(reinterpret_cast<char*>(&net), sizeof(net));
}

// Escreve double em big-endian
void ProdutoOutputStream::writeDouble(double value) {
    static_assert(sizeof(double) == 8, "Double deve ter 8 bytes");

    uint64_t temp;
    std::memcpy(&temp, &value, sizeof(double));

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    temp = __builtin_bswap64(temp);
#endif

    out.write(reinterpret_cast<char*>(&temp), sizeof(temp));
}

// Escreve string como [tamanho][bytes]
void ProdutoOutputStream::writeString(const std::string& str) {
    writeInt(static_cast<int>(str.size()));
    out.write(str.data(), str.size());
}

// Método principal de escrita
void ProdutoOutputStream::write() {
    // Quantidade de produtos
    writeInt(qtd);

    for (int i = 0; i < qtd; ++i) {
        const Produto& p = produtos[i];

        writeInt(p.getId());
        writeString(p.getNome());
        writeString(p.getDescricao());
        writeDouble(p.getPreco());
        writeInt(p.getQuantidadeEstoque());
    }
}