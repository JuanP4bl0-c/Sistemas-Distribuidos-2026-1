package Servidor_java.Serializacao;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import Servidor_java.Modelos.Celular;
import Servidor_java.Servicos.CatalogoCelular;

import Servidor_java.Stream.*;

public class Request {

    public static final int OP_LISTAR = 1;           
    public static final int OP_ADICIONAR = 2;        
    public static final int OP_REMOVER = 3; 

    public static final int RESP_OK = 200; 

    // private DataInputStream entrada;
    private InputStream entrada;
    private OutputStream saida;

    public Request(InputStream entrada, OutputStream saida) {
        this.entrada = entrada;
        this.saida = saida;
    }

    public void enviarResposta(int codigo) throws IOException {

        byte[] buffer = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(codigo).array();
        saida.write(buffer);
        saida.flush();

    }

    public int obterOperacao() throws IOException {
        byte[] op_buffer = new byte[4];
        int bytes_lidos = entrada.read(op_buffer);
        
        if (bytes_lidos <= 0) {
            return -1;  // Cliente desconectou
        }
        
        return ByteBuffer.wrap(op_buffer).order(ByteOrder.LITTLE_ENDIAN).getInt();
    }


    public void processarRequisicao(CatalogoCelular catalogo, int operacao) throws IOException {
        System.out.println("Operação recebida: " + operacao);
        
        switch(operacao) {
            case OP_LISTAR:
                System.out.println("LISTAR - Enviando catálogo");
                enviarResposta(RESP_OK);
                listarCatalogo(catalogo);
                break;
                
            case OP_ADICIONAR:
                System.out.println("ADICIONAR - Recebendo produtos");
                enviarResposta(RESP_OK);
                adicionarProdutos(catalogo);
                break;
                
            case OP_REMOVER:
                System.out.println("REMOVER - Removendo produto");
                enviarResposta(RESP_OK);
                removerCelular(catalogo);
                break;
                
            default:
                System.out.println("Operação desconhecida: " + operacao);
                enviarResposta(0);
        }
    }


    private void listarCatalogo(CatalogoCelular catalogo) throws IOException {
        var lista = catalogo.getTodos();
        Celular[] array = lista.toArray(new Celular[0]);
        
        PojoOutputStream pos = new PojoOutputStream(array, array.length, saida);
        pos.enviarDados();

    }

    
    
    private void adicionarProdutos(CatalogoCelular catalogo) throws IOException {
        // Lê tamanho do pacote
        byte[] tam_buffer = new byte[4];
        entrada.read(tam_buffer);
        int tamanho = ByteBuffer.wrap(tam_buffer)
            .order(ByteOrder.BIG_ENDIAN)
            .getInt();
        
        // Lê dados
        byte[] data_buffer = new byte[tamanho];
        entrada.read(data_buffer);
        
        // Desserializa
        PojoInputstream pis = new PojoInputstream(new ByteArrayInputStream(data_buffer));
        int qtd = pis.lerInt_LE();
        
        for(int i = 0; i < qtd; i++) {
            Celular c = pis.lerCelular_LE();
            catalogo.adicionarCelular(c);
            System.out.println("  Adicionado: " + c.getNome());
        }
    }
    
    private void removerCelular(CatalogoCelular catalogo) throws IOException {
        byte[] id_buffer = new byte[4];
        entrada.read(id_buffer);
        int id = ByteBuffer.wrap(id_buffer)
            .order(ByteOrder.LITTLE_ENDIAN)
            .getInt();
        
        catalogo.removerCelular(id);  // ✅ Agora remove de verdade
        System.out.println("  Removido: ID " + id);
    }
    
}