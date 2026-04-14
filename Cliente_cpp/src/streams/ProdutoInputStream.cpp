#include "streams/ProdutoInputStream.h"
#include <arpa/inet.h>   // ntohl
#include <cstring>
#include <cstdint>
#include <stdexcept>

// Construtor
ProdutoInputStream::ProdutoInputStream(std::istream& in) : in(in) {}

// 🔹 Lê inteiro em big-endian
int ProdutoInputStream::readInt() {
    uint32_t net;
    in.read(reinterpret_cast<char*>(&net), sizeof(net));

    if (!in)
        throw std::runtime_error("Erro ao ler inteiro do stream.");

    return static_cast<int>(ntohl(net));
}

// 🔹 Lê double em big-endian
double ProdutoInputStream::readDouble() {
    uint64_t temp;
    in.read(reinterpret_cast<char*>(&temp), sizeof(temp));

    if (!in)
        throw std::runtime_error("Erro ao ler double do stream.");

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    temp = __builtin_bswap64(temp);
#endif

    double value;
    std::memcpy(&value, &temp, sizeof(double));
    return value;
}

// 🔹 Lê string no formato [tamanho][bytes]
std::string ProdutoInputStream::readString() {
    int size = readInt();

    if (size < 0)
        throw std::runtime_error("Tamanho de string inválido.");

    std::string str(size, '\0');
    in.read(&str[0], size);

    if (!in)
        throw std::runtime_error("Erro ao ler string do stream.");

    return str;
}

// 🔹 Lê todos os produtos
std::vector<Produto> ProdutoInputStream::read() {
    std::vector<Produto> lista;

    int qtd = readInt();

    for (int i = 0; i < qtd; ++i) {
        int id = readInt();
        std::string nome = readString();
        std::string descricao = readString();
        double preco = readDouble();
        int estoque = readInt();

        lista.emplace_back(id, nome, descricao, preco, estoque);
    }

    return lista;
}