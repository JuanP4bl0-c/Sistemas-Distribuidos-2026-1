package Servidor_java.Modelos;

// Esta classe representa a estrutura da Figura 5.2 do livro
public class MensagemRPC {
    
    public int messageType; // 0 = Request, 1 = Reply
    public int requestId;   // ID único da mensagem
    public String objectReference; // Nome do objeto remoto (ex: "CatalogoRemoto")
    public int methodId;    // 1=Listar, 2=Add, 3=Remover, 4=Buscar
    public String arguments; // O JSON do Produto propriamente dito vai aqui dentro como String!

    // Construtor vazio para o Gson
    public MensagemRPC() {}
}