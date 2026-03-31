package Servidor_java.Stream;

import java.io.*;
import java.nio.*;

import javax.imageio.stream.ImageInputStream;

import Servidor_java.Modelos.Celular;


public class PojoInputstream extends FilterInputStream{
 
    public PojoInputstream(InputStream entrada) {super(entrada);}   

    public int lerIntLE() throws IOException{
        byte[] buffer = new byte[4];
        this.read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getInt();
    }

    // Método auxiliar para ler um Float em Little Endian
    private float lerFloatLE() throws IOException {
        byte[] buffer = new byte[4];
        read(buffer);
        return ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getFloat();
    }

    // Método para ler uma String (Tamanho + caracteres)
    private String lerString() throws IOException {
        int tam = lerIntLE();
        byte[] buffer = new byte[tam];
        read(buffer);
        return new String(buffer);
    }

    public Celular lerCelular() throws IOException {

        int id = lerIntLE();
        String nome = lerString();
        String descricao = lerString();
        float preco = lerFloatLE();
        int estoque = lerIntLE();


        return new Celular(id, nome, descricao, (double)preco, estoque, "Desconhecida", "Desconhecido");
    }
}
