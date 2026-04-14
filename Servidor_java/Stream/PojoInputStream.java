package Servidor_java.Stream;

import java.io.*;
import java.nio.*;


import Servidor_java.Modelos.*;


public class PojoInputStream extends FilterInputStream{

    
    public PojoInputStream(InputStream entrada) {super(entrada);}   


    //Leitura em dados sem formato
    public int lerInt() throws IOException{
        byte[] buffer = new byte[4];
        this.read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getInt();
    }

    private double lerDouble() throws IOException {
        byte[] buffer = new byte[8];
        read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getDouble();
    }

    private String lerString() throws IOException {
        int tam = lerInt();
        byte[] buffer = new byte[tam];
        read(buffer);
        return new String(buffer);
    }


    // Leitura de objetos e suas subclasses

    private static class BaseProduto {
        
        int id;
        String nome;
        String descricao;
        double preco;
        int estoque;

        BaseProduto(int id, String nome, String descricao, double preco, int estoque) {
            this.id = id;
            this.nome = nome;
            this.descricao = descricao;
            this.preco = preco;
            this.estoque = estoque;
        }
    }
    
    private BaseProduto lerCamposBase() throws IOException {
        int id = lerInt();
        String nome = lerString();
        String descricao = lerString();
        double preco = lerDouble();
        int estoque = lerInt();
        return new BaseProduto(id, nome, descricao, preco, estoque);
    }

    public Celular lerCelular() throws IOException {
        BaseProduto base = lerCamposBase();
        String marca = lerString();
        String modelo = lerString();
        return new Celular(base.id, base.nome, base.descricao, base.preco, base.estoque, marca, modelo);
    }

    public Capa lerCapa() throws IOException {
        BaseProduto base = lerCamposBase();
        String modelo = lerString();
        String material = lerString();
        return new Capa(base.id, base.nome, base.descricao, base.preco, base.estoque, modelo, material);
    }

    public Pelicula lerPelicula() throws IOException {
        BaseProduto base = lerCamposBase();
        String modelo = lerString();
        String material = lerString();
        return new Pelicula(base.id, base.nome, base.descricao, base.preco, base.estoque, modelo, material);
    }

    public PowerBank lerPowerBank() throws IOException {
        BaseProduto base = lerCamposBase();
        String marca = lerString();
        String modelo = lerString();
        int capacidade = lerInt();
        return new PowerBank(base.id, base.nome, base.descricao, base.preco, base.estoque, marca, modelo, capacidade);
    }

    public Produto lerProduto() throws IOException {
        int tipo = lerInt();
        
        switch(tipo) {
            case 1:
                return lerCelular();
            case 2:
                return lerPowerBank();
            case 3:
                return lerCapa();
            case 4:
                return lerPelicula();
            default:
                // Fallback: lê apenas campos base
                BaseProduto base = lerCamposBase();
                return new Produto(base.id, base.nome, base.descricao, base.preco, base.estoque);
        }
    }

    /*
        Seção de Request/Reply
    */


    public int obterOperacao() throws IOException { 
        byte[] op_buffer = new byte[4];
        int bytes_lidos = this.read(op_buffer);
        
        if (bytes_lidos <= 0) {
            return -1;
        }
        
        return ByteBuffer.wrap(op_buffer).order(ByteOrder.BIG_ENDIAN).getInt();
    }


    public int obterOperacao1() throws IOException { 
        // 1. Lê os primeiros 4 bytes (Tamanho total do payload enviado pelo C++)
        byte[] tamanho_buffer = new byte[4];
        int bytes_lidos = this.read(tamanho_buffer);
        if (bytes_lidos <= 0) return -1;
        
        // int tamanhoPayload = ByteBuffer.wrap(tamanho_buffer).order(ByteOrder.BIG_ENDIAN).getInt();
        // (Opcional: você pode usar o tamanhoPayload para validar a leitura dos próximos bytes)

        // 2. Agora sim, lê a Operação (ADICIONAR = 2, etc.)
        byte[] op_buffer = new byte[4];
        this.read(op_buffer);
        return ByteBuffer.wrap(op_buffer).order(ByteOrder.BIG_ENDIAN).getInt();
    }

}
