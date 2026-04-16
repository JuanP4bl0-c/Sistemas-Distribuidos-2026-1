#include "streams/ProdutoInputStream.h"
#include <arpa/inet.h>   // ntohl
#include <cstring>
#include <cstdint>
#include <stdexcept>

// 🔹 Construtor
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

// 🔹 Lê todos os produtos com suporte a subclasses
std::vector<std::shared_ptr<Produto>> ProdutoInputStream::read() {
    std::vector<std::shared_ptr<Produto>> lista;

    int qtd = readInt();
    if (qtd < 0)
        throw std::runtime_error("Quantidade de produtos inválida.");

    for (int i = 0; i < qtd; ++i) {
        // 🔹 Lê o tipo do produto
        TipoProduto tipo = static_cast<TipoProduto>(readInt());

        // 🔹 Atributos comuns
        int id = readInt();
        std::string nome = readString();
        std::string descricao = readString();
        double preco = readDouble();
        int estoque = readInt();

        std::shared_ptr<Produto> produto;

        // 🔹 Instancia a subclasse correta
        switch (tipo) {
            case TipoProduto::CELULAR: {
                std::string marca = readString();
                std::string modelo = readString();
                produto = std::make_shared<Celular>(
                    id, nome, descricao, preco, estoque, marca, modelo);
                break;
            }
            case TipoProduto::CAPA: {
                std::string modelo = readString();
                std::string material = readString();
                produto = std::make_shared<Capa>(
                    id, nome, descricao, preco, estoque, modelo, material);
                break;
            }
            case TipoProduto::PELICULA: {
                std::string modelo = readString();
                std::string material = readString();
                produto = std::make_shared<Pelicula>(
                    id, nome, descricao, preco, estoque, modelo, material);
                break;
            }
            case TipoProduto::POWERBANK: {
                std::string marca = readString();
                std::string modelo = readString();
                int capacidade = readInt();
                produto = std::make_shared<PowerBank>(
                    id, nome, descricao, preco, estoque, marca, modelo, capacidade);
                break;
            }
            case TipoProduto::PRODUTO:
            default: {
                produto = std::make_shared<Produto>(
                    id, nome, descricao, preco, estoque);
                break;
            }
        }

        lista.push_back(produto);
    }

    return lista;
}