package Servidor_java;

import java.util.List;

import Servidor_java.Modelos.Capa;
import Servidor_java.Modelos.Celular;
import Servidor_java.Modelos.Pelicula;
import Servidor_java.Modelos.PowerBank;
import Servidor_java.Modelos.Produto;
import Servidor_java.Servicos.CatalogoProdutos;

public class ProdutoController {

    private final CatalogoProdutos catalogo;

    public ProdutoController() {
        this.catalogo = new CatalogoProdutos();
        this.catalogo.AdicionarProduto(new Celular(1, "IPhone 15", "Apple", 5000.0, 5, "Apple", "15 Pro"));
        this.catalogo.AdicionarProduto(new Capa(2, "Capa Iphone", "Azul", 15, 20, "Iphone 15", "Plastico"));
        this.catalogo.AdicionarProduto(new Pelicula(3, "Pelicula", "5 pol", 25.50, 15, "Iphone 15", "Vidro"));
        this.catalogo.AdicionarProduto(new PowerBank(4, "Power Bank", "Bateria", 200.0, 10, "Xiaomi", "10000mAh", 1000));
    }

    public synchronized List<Produto> listarTodos() {
        return this.catalogo.getTodos();
    }

    public synchronized Produto buscarPorId(int id) {
        return this.catalogo.GetProduto(id);
    }

    public synchronized void adicionarProduto(Produto produto) {
        this.catalogo.AdicionarProduto(produto);
    }

    public synchronized boolean removerProduto(int id) {
        Produto existente = this.catalogo.GetProduto(id);
        if (existente == null) {
            return false;
        }
        this.catalogo.RemoverProduto(id);
        return true;
    }
}