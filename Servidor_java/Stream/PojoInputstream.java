package Servidor_java.Stream;

import java.io.*;
import java.nio.*;


import Servidor_java.Modelos.Celular;


public class PojoInputstream extends FilterInputStream{
 
    public PojoInputstream(InputStream entrada) {super(entrada);}   

    public int lerInt() throws IOException{
        byte[] buffer = new byte[4];
        this.read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getInt();
    }
    
    public int lerInt_LE() throws IOException{
        byte[] buffer = new byte[4];
        this.read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getInt();
    }

    private float lerFloat() throws IOException {
        byte[] buffer = new byte[4];
        read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getFloat();
    }

    private float lerFloat_LE() throws IOException {
        byte[] buffer = new byte[4];
        read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getFloat();
    }

    private double lerDouble_LE() throws IOException {
        byte[] buffer = new byte[8];
        read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getDouble();
    }

    // Método para ler uma String (Tamanho + caracteres)
    private String lerString() throws IOException {
        int tam = lerInt();
        byte[] buffer = new byte[tam];
        read(buffer);
        return new String(buffer);
    }

    private String lerString_LE() throws IOException {
        int tam = lerInt_LE();
        byte[] buffer = new byte[tam];
        read(buffer);
        return new String(buffer);
    }

    public Celular lerCelular() throws IOException {

        int id = lerInt();
        String nome = lerString();
        String descricao = lerString();
        float preco = lerFloat();
        int estoque = lerInt();


        return new Celular(id, nome, descricao, (double)preco, estoque, "Desconhecida", "Desconhecido");
    }

    public Celular lerCelular_LE() throws IOException {

        int id = lerInt_LE();
        String nome = lerString_LE();
        String descricao = lerString_LE();
        double preco = lerDouble_LE();
        int estoque = lerInt_LE();


        return new Celular(id, nome, descricao, preco, estoque, "Desconhecida", "Desconhecido");
    }
}
