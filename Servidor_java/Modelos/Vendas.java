package Servidor_java.Modelos;

public class Vendas {
    private final Vendedor vendedor; // Alterado de Gestor para Vendedor
    private final Produto produto;
    private final int quantidade;
    private final double subtotal;

    public Vendas (Vendedor vendedor, Produto produto, int quantidade) {
        this.vendedor = vendedor;
        this.produto = produto;
        this.quantidade = quantidade;
        this.subtotal = produto.getPreco() * quantidade;
    }

    public String obterResumoVenda(){
        String resumo = "Produto: " + produto.getNome();
        resumo += " | Qtd: " + quantidade;
        resumo += " | Preço final: R$ " + subtotal;
        
        // Agregação em ação:
        if (vendedor != null && !vendedor.getNome().isEmpty()) {
            resumo += " | Vendedor responsável: " + vendedor.getNome() + " (ID: " + vendedor.getId() + ")";
        } else {
            resumo += " | Venda direta (Sem vendedor)";
        }

        return resumo;
    }

    public double getSubtotal() {
        return this.subtotal;
    }
}