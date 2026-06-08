package Servidor_java.Modelos;

public class Vendedor {
    private String id;
    private String nome;

    public Vendedor(String id, String nome) {
        this.id = id;
        this.nome = nome;
    }

    public String getId() { return id; }
    public String getNome() { return nome; }
}