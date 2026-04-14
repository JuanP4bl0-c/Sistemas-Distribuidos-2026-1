package Servidor_java.Servicos;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.List;

import Servidor_java.Modelos.*;
import Servidor_java.Stream.PojoInputstream;
import Servidor_java.Stream.PojoOutputStream;

public class CatalogoProdutos {
    
    private List<Produto> ListaGeral;

    public CatalogoProdutos() {
        this.ListaGeral = new ArrayList<>();
    }

    public void AdicionarProduto(Produto ProdutoNovo){
        ListaGeral.add(ProdutoNovo);
        System.out.println("Produto "+ProdutoNovo.getNome()+" Adicionado ao catalogo.");
    }

    public Produto GetProduto(int id){
        
        for(Produto p : ListaGeral){
            if (p.getId() == id) {
                return p;
            }
        }

        return null;
    }

    public <Tipo extends Produto> List<Tipo> buscarPorTipo(Class<Tipo> tipo){
        
        List<Tipo> resultado = new ArrayList<>();

        for (Produto p : ListaGeral){
            if (tipo.isInstance(p)) {
                resultado.add(tipo.cast(p));
            }
        }

        return resultado;
    }

    public void RemoverProduto(int id){
        ListaGeral.removeIf(p -> p.getId() == id);
    }

    public List<Produto> getTodos(){return ListaGeral;}



    public void listarCatalogo_Stream(InputStream entrada, OutputStream saida) throws IOException {
        var lista = this.getTodos();
        Produto[] array = lista.toArray(new Produto[0]);
        
        PojoOutputStream pos = new PojoOutputStream(array, array.length, saida);
        pos.enviarDados();
    }

    
    
    public void AdicionarProdutos_Stream(InputStream entrada, OutputStream saida) throws IOException {
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
            this.AdicionarProduto(c);
            System.out.println("  Adicionado: " + c.getNome());
        }
        
    }
    
    public void RemoverProduto_Stream(InputStream entrada, OutputStream saida) throws IOException {
        byte[] id_buffer = new byte[4];
        entrada.read(id_buffer);
        int id = ByteBuffer.wrap(id_buffer)
            .order(ByteOrder.LITTLE_ENDIAN)
            .getInt();
        
        this.RemoverProduto(id);
        System.out.println("  Removido: ID " + id);
    }



}
