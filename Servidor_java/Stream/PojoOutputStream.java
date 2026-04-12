package Servidor_java.Stream;

import java.io.*;
import java.nio.*;
import java.nio.charset.StandardCharsets;

import Servidor_java.Modelos.Celular;

public class PojoOutputStream extends FilterOutputStream {
    
    
    private Celular[] produtos;
    private int qtd_produtos;
    
    
    
    // Construtor exigido pela Questão 2, item 'a'
    public PojoOutputStream(Celular[] produtos,int qtd_produtos, OutputStream out) {
        super(out);
        this.produtos = produtos;
        this.qtd_produtos = qtd_produtos;
    }

    private void escreverInt(int valor) throws IOException {
        byte[] buffer = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(valor).array();
        out.write(buffer);
    }

    private void escreverDouble(double valor) throws IOException {
    byte[] buffer = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN).putDouble(valor).array();
    out.write(buffer);
    }

    // Método auxiliar para enviar String com tamanho dinâmico
    private void escreverString(String texto) throws IOException {
        byte[] stringBytes = texto.getBytes(StandardCharsets.UTF_8);
        escreverInt(stringBytes.length);
        out.write(stringBytes);
    }

    // Método principal para disparar os dados
    public void enviarDados() throws IOException {
        
        escreverInt(qtd_produtos);

        for (int i = 0; i < qtd_produtos; i++) {
            Celular c = produtos[i];
            
            // O trabalho pede PELO MENOS 3 atributos. Vamos enviar 4:
            escreverInt(c.getId());
            escreverString(c.getNome());
            escreverString(c.getDescricao());
            escreverDouble((float) c.getPreco());
        }
        out.flush(); // Empurra os dados pela rede
    }
}