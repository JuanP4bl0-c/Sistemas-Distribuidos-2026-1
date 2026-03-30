#include "streams/ProdutoOutPutStream.h"

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
        float preco = p.getPreco();
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
        out.write((char*)&preco, sizeof(float));

        // estoque
        out.write((char*)&estoque, sizeof(int));
    }
}