package Servidor_java.Utils;

import java.io.*;
import java.nio.*;

import Servidor_java.Modelos.Celular;
import Servidor_java.Modelos.Produto;

import Servidor_java.Servicos.CatalogoProdutos;

import Servidor_java.Stream.PojoInputstream;
import Servidor_java.Stream.PojoOutputStream;

public class FileOutputStream_catalogo {
    
    private static final String Catalogo_file = "Servidor_java/catalogo.bin";
    private static final String Catalogo_CSV = "Servidor_java/catalogo.csv";


    public static void salvarCatalogo(CatalogoProdutos catalogo) {
        try (FileOutputStream fos = new FileOutputStream(Catalogo_file)) {
            var lista = catalogo.getTodos();
            Produto[] array = lista.toArray(new Produto[0]);
            
            PojoOutputStream pos = new PojoOutputStream(array, array.length, fos);
            pos.enviarDados();
            
            System.out.println("Catálogo salvo com sucesso!");
        } catch (IOException e) {
            System.out.println("Erro ao salvar catálogo: " + e.getMessage());
        }
    }

    public static void carregarCatalogo(CatalogoProdutos catalogo) {
        File arquivo = new File(Catalogo_file);
        
        if (!arquivo.exists()) {
            System.out.println("Arquivo de catálogo não encontrado. Iniciando com valores padrão.");
            return;
        }
        
        try (FileInputStream fis = new FileInputStream(Catalogo_file)) {
            byte[] qtd_bytes = new byte[4];
            fis.read(qtd_bytes);
            int quantidade = ByteBuffer.wrap(qtd_bytes)
                .order(ByteOrder.LITTLE_ENDIAN)
                .getInt();
            
            System.out.println("Carregando " + quantidade + " produtos do arquivo...");
            
            PojoInputstream pis = new PojoInputstream(fis);
            
            for (int i = 0; i < quantidade; i++) {
                Celular c = pis.lerCelular_LE();
                catalogo.AdicionarProduto(c);
                System.out.println("  Carregado: " + c.getNome());
            }
            
        } catch (IOException e) {
            System.out.println("Erro ao carregar catálogo: " + e.getMessage());
        }
    }

    public static void salvarCatalogoCsv(CatalogoProdutos catalogo) {
        try (FileWriter fw = new FileWriter(Catalogo_CSV)) {
            // Cabeçalho
            fw.write("ID,Nome,Descricao,Preco,Estoque,Marca,Modelo\n");
            
            // Dados
            for (Produto p : catalogo.getTodos()) {
                Celular c = (Celular) p;
                fw.write(c.getId() + "," +
                        c.getNome() + "," +
                        c.getDescricao() + "," +
                        c.getPreco() + "," +
                        c.getEstoque() + "," +
                        c.getMarca() + "," +
                        c.getModelo() + "\n");
            }
            
            System.out.println("Catálogo CSV salvo em: " + Catalogo_CSV);
        } catch (IOException e) {
            System.out.println("Erro ao salvar CSV: " + e.getMessage());
        }
    }

}