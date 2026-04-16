#include "streams/ProdutoOutPutStream.h"
<<<<<<< HEAD

ProdutoOutputStream::ProdutoOutputStream(const std::vector<Produto>& produtos, int qtd, std::ostream& out)
    : produtos(produtos), qtd(qtd), out(out) {}

void ProdutoOutputStream::write() {
    // envia quantidade
    out.write((char*)&qtd, sizeof(int));

    for (int i = 0; i < qtd; i++) {
        const Produto& p = produtos[i];

        int id = p.getId();
        int tam_nome = p.getNome().size();
        int tam_desc = p.getDescricao().size();
        double preco = p.getPreco();
        int estoque = p.getQuantidadeEstoque();

        // id
        out.write((char*)&id, sizeof(int));

        // nome
        out.write((char*)&tam_nome, sizeof(int));
        out.write(p.getNome().c_str(), tam_nome);

        // descrição
        out.write((char*)&tam_desc, sizeof(int));
        out.write(p.getDescricao().c_str(), tam_desc);

        // preco
        out.write((char*)&preco, sizeof(double));

        // estoque
        out.write((char*)&estoque, sizeof(int));
=======
#include <arpa/inet.h>   // htonl
#include <cstring>
#include <cstdint>
#include <stdexcept>

// 🔹 Construtor
ProdutoOutputStream::ProdutoOutputStream(
    const std::vector<std::shared_ptr<Produto>>& produtos,
    int qtd,
    std::ostream& out)
    : produtos(produtos), qtd(qtd), out(out) {}

// 🔹 Escreve inteiro em big-endian
void ProdutoOutputStream::writeInt(int value) {
    uint32_t net = htonl(static_cast<uint32_t>(value));
    out.write(reinterpret_cast<char*>(&net), sizeof(net));
}

// 🔹 Escreve double em big-endian
void ProdutoOutputStream::writeDouble(double value) {
    static_assert(sizeof(double) == 8, "Double deve ter 8 bytes");

    uint64_t temp;
    std::memcpy(&temp, &value, sizeof(double));

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    temp = __builtin_bswap64(temp);
#endif

    out.write(reinterpret_cast<char*>(&temp), sizeof(temp));
}

// 🔹 Escreve string como [tamanho][bytes]
void ProdutoOutputStream::writeString(const std::string& str) {
    writeInt(static_cast<int>(str.size()));
    out.write(str.data(), str.size());
}

// 🔹 Serializa um produto considerando seu tipo
void ProdutoOutputStream::writeProduto(const std::shared_ptr<Produto>& produto) {
    // 1. Escreve o tipo do produto
    writeInt(static_cast<int>(produto->getTipo()));

    // 2. Atributos comuns
    writeInt(produto->getId());
    writeString(produto->getNome());
    writeString(produto->getDescricao());
    writeDouble(produto->getPreco());
    writeInt(produto->getQuantidadeEstoque());

    // 3. Atributos específicos de cada subclasse
    switch (produto->getTipo()) {
        case TipoProduto::CELULAR: {
            auto celular = std::dynamic_pointer_cast<Celular>(produto);
            if (!celular)
                throw std::runtime_error("Erro de conversão para Celular");

            writeString(celular->getMarca());
            writeString(celular->getModelo());
            break;
        }
        case TipoProduto::CAPA: {
            auto capa = std::dynamic_pointer_cast<Capa>(produto);
            if (!capa)
                throw std::runtime_error("Erro de conversão para Capa");
            writeString(capa->getModelo());
            writeString(capa->getMaterial());
            break;
        }
        case TipoProduto::PELICULA: {
            auto pelicula = std::dynamic_pointer_cast<Pelicula>(produto);
            if (!pelicula)
                throw std::runtime_error("Erro de conversão para Pelicula");

            writeString(pelicula->getModelo());
            writeString(pelicula->getMaterial());
            break;
        }
        case TipoProduto::POWERBANK: {
            auto powerbank = std::dynamic_pointer_cast<PowerBank>(produto);
            if (!powerbank)
                throw std::runtime_error("Erro de conversão para PowerBank");

            writeString(powerbank->getMarca());
            writeString(powerbank->getModelo());
            writeInt(powerbank->getCapacidade());
            break;
        }
        case TipoProduto::PRODUTO:
        default:
            // Produto base não possui atributos adicionais
            break;
    }
}

// 🔹 Método principal
void ProdutoOutputStream::write() {
    // Escreve a quantidade de produtos
    writeInt(qtd);

    for (int i = 0; i < qtd; ++i) {
        writeProduto(produtos[i]);
>>>>>>> 3a786a2 (Cliente_cpp atualizada da branch client_cpp)
    }
}