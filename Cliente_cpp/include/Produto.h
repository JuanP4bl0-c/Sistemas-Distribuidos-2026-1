class Produto{
protected;
    int id;
    std::string nome;
    double preco;

public:
    Produto(int id, std::string nome, double preco){}

    virtual ~Produto() {}

    virtual void mostrar(){}
    int getID() const{}
    std::string getNome() const{}
    double getPreco() const{}
};