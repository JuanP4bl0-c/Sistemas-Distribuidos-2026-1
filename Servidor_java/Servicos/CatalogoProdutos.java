package Servidor_java.Servicos;

import java.util.ArrayList;
import java.util.List;

import Servidor_java.Modelos.*;

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

}
