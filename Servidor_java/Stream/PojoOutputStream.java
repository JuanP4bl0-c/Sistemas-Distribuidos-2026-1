package Servidor_java.Stream;

import java.io.*;
import java.nio.*;
import java.nio.charset.StandardCharsets;

import Servidor_java.Modelos.Produto;

public class PojoOutputStream extends FilterOutputStream {
    
    
    private Produto[] produtos;
    private int qtd_produtos;
    
    public PojoOutputStream(Produto[] produtos,int qtd_produtos, OutputStream out) {
        super(out);
        this.produtos = produtos;
        this.qtd_produtos = qtd_produtos;
    }

    private void escreverInt(int valor) throws IOException {
        byte[] buffer = ByteBuffer.allocate(4).order(ByteOrder.BIG_ENDIAN).putInt(valor).array();
        out.write(buffer);
    }

    private void escreverDouble(double valor) throws IOException {
    byte[] buffer = ByteBuffer.allocate(8).order(ByteOrder.BIG_ENDIAN).putDouble(valor).array();
    out.write(buffer);
    }

    private void escreverString(String texto) throws IOException {
        byte[] stringBytes = texto.getBytes(StandardCharsets.UTF_8);
        escreverInt(stringBytes.length);
        out.write(stringBytes);
    }

    public void enviarDados() throws IOException {
        
        escreverInt(qtd_produtos);

        for (int i = 0; i < qtd_produtos; i++) {
            Produto c = produtos[i];
            
            escreverInt(c.getId());
            escreverString(c.getNome());
            escreverString(c.getDescricao());
            escreverDouble((float) c.getPreco());
        }
        out.flush();
    }

    /* 
        Reply
    */

    public void enviarResposta(int codigo) throws IOException {
        byte[] buffer = ByteBuffer.allocate(4).order(ByteOrder.BIG_ENDIAN).putInt(codigo).array();
        out.write(buffer);
        out.flush();
    }

    
}