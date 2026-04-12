#include <string>

class Produto{
protected:
    int id;
    std::string nome;
    double preco;

public:
    Produto(int id, std::string nome, double preco);

    virtual ~Produto() = default;

    virtual void mostrar() const;
    int getId() const;
    std::string getNome() const;
    double getPreco() const;
    void setId(int id);
    void setNome(const std::string& nome);
    void setPreco(double preco);
};