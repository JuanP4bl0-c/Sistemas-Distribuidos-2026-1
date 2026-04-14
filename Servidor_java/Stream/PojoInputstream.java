package Servidor_java.Stream;

import java.io.*;
import java.nio.*;


import Servidor_java.Modelos.*;


public class PojoInputstream extends FilterInputStream{

    
    public PojoInputstream(InputStream entrada) {super(entrada);}   


    //Leitura em dados sem formato

    public int lerInt() throws IOException{
        byte[] buffer = new byte[4];
        this.read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getInt();
    }
    
    public int lerInt_LE() throws IOException{
        byte[] buffer = new byte[4];
        this.read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getInt();
    }

    private double lerDouble_LE() throws IOException {
        byte[] buffer = new byte[8];
        read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getDouble();
    }

    private String lerString_LE() throws IOException {
        int tam = lerInt_LE();
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
    
    private BaseProduto lerCamposBase_LE() throws IOException {
        int id = lerInt_LE();
        String nome = lerString_LE();
        String descricao = lerString_LE();
        double preco = lerDouble_LE();
        int estoque = lerInt_LE();
        return new BaseProduto(id, nome, descricao, preco, estoque);
    }

    public Celular lerCelular_LE() throws IOException {
        BaseProduto base = lerCamposBase_LE();
        String marca = lerString_LE();
        String modelo = lerString_LE();
        return new Celular(base.id, base.nome, base.descricao, base.preco, base.estoque, marca, modelo);
    }

    public Capa lerCapa_LE() throws IOException {
        BaseProduto base = lerCamposBase_LE();
        String modelo = lerString_LE();
        String material = lerString_LE();
        return new Capa(base.id, base.nome, base.descricao, base.preco, base.estoque, modelo, material);
    }

    public Pelicula lerPelicula_LE() throws IOException {
        BaseProduto base = lerCamposBase_LE();
        String modelo = lerString_LE();
        String material = lerString_LE();
        return new Pelicula(base.id, base.nome, base.descricao, base.preco, base.estoque, modelo, material);
    }

    public PowerBank lerPowerBank_LE() throws IOException {
        BaseProduto base = lerCamposBase_LE();
        String marca = lerString_LE();
        String modelo = lerString_LE();
        int capacidade = lerInt_LE();
        return new PowerBank(base.id, base.nome, base.descricao, base.preco, base.estoque, marca, modelo, capacidade);
    }

    public Produto lerProduto_LE() throws IOException {
        int tipo = lerInt_LE();
        
        switch(tipo) {
            case 1:
                return lerCelular_LE();
            case 2:
                return lerPowerBank_LE();
            case 3:
                return lerCapa_LE();
            case 4:
                return lerPelicula_LE();
            default:
                // Fallback: lê apenas campos base
                BaseProduto base = lerCamposBase_LE();
                return new Produto(base.id, base.nome, base.descricao, base.preco, base.estoque);
        }
    }

    /*
        Seção de Request/Reply
    */


    public int ObterOperacao(int op) throws IOException {
        byte[] op_buffer = new byte[4];
        int bytes_lidos = this.read(op_buffer);
        
        if (bytes_lidos <= 0) {
            return -1;  // Cliente desconectou
        }
        
        return ByteBuffer.wrap(op_buffer).order(ByteOrder.BIG_ENDIAN).getInt();
    }

}
