#include "Produto.h"

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5001);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");

    connect(sock, (sockaddr*)&server, sizeof(server));

    Produto p(1, "Carregador", "Carregador para smartphone", 79.90, 50 );

    // 🔹 serialização
    int id = p.getId();
    int tamanho = p.getNome().size();
    int descricao_tamanho = p.getDescricao().size();
    int quantidade_estoque = p.getQuantidadeEstoque();
    float preco = p.getPreco();

    // envia id
    send(sock, &id, sizeof(int), 0);

    // envia tamanho do nome
    send(sock, &tamanho, sizeof(int), 0);

    // envia nome
    send(sock, p.getNome().c_str(), tamanho, 0);

    //envia tamanho da descrição
    send(sock, &descricao_tamanho, sizeof(int), 0);
    // envia descrição
    send(sock, p.getDescricao().c_str(), descricao_tamanho, 0);

    // envia preco
    send(sock, &preco, sizeof(float), 0);

    // envia quantidade em estoque
    send(sock, &quantidade_estoque, sizeof(int), 0);

    close(sock);
    return 0;
}