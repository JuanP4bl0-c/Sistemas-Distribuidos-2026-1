#include "streams/ProdutoInPutStream.h"
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <cstring>

ProdutoInputStream::ProdutoInputStream(std::istream& entrada) : entrada(entrada) {}

int ProdutoInputStream::readInt(){
    int value;
    entrada.read(reinterpret_cast<char*>(&value), sizeof(int));
    return ntohl(value);  // Converte de BIG_ENDIAN para host
}

float ProdutoInputStream::readFloat(){
    float value;
    entrada.read(reinterpret_cast<char*>(&value), sizeof(float));
    return value;
}

double ProdutoInputStream::readDouble(){
    double value;
    entrada.read(reinterpret_cast<char*>(&value), sizeof(double));
    return value;
}

std::string ProdutoInputStream::readString(){
    int size = readInt();
    std::vector<char> buffer(size);
    entrada.read(buffer.data(), size);
    return std::string(buffer.data(), size);
}

Produto ProdutoInputStream::readProduto(){
    int id = readInt();
    std::string nome = readString();
    std::string descricao = readString();
    double preco = readDouble();
    int quantidadeEstoque = readInt();

    return Produto(id, nome, descricao, preco, quantidadeEstoque);
}

