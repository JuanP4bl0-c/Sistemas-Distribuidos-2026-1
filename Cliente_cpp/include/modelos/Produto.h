#include <string>

class Produto{
protected:
    int id;
    std::string nome;
    std::string descricao;
    float preco;
    int quantidade_estoque;

public:
    Produto(int id, std::string nome, std::string descricao, float preco, int quantidade_estoque);

    virtual ~Produto() = default;

    virtual void mostrar() const;
    int getId() const;
    std::string getNome() const;
    std::string getDescricao() const;
    float getPreco() const;
    int getQuantidadeEstoque() const;
    void setId(int id);
    void setNome(const std::string& nome);
    void setDescricao(const std::string& descricao);
    void setPreco(float preco);
    void setQuantidadeEstoque(int quantidade_estoque);
};