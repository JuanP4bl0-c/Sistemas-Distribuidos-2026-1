package Servidor_java.Servicos;

import Servidor_java.Modelos.Celular;


/**
 * GestorVendas: componente que contém regras de negócio para vendas.
 *
 * Fornece operações como processar uma venda (atualiza estoque) e calcular
 * preço à vista com desconto. Implementações simples voltadas para demonstração.
 */
public class GestorVendas {

    /**
     * Tenta processar a venda de `quantidade` unidades do `celular`.
     * Retorna `true` em caso de sucesso (estoque suficiente) ou `false` caso contrário.
     */
    public boolean processarVenda(Celular celular, int quantidade) {
        if (celular == null) return false;

        if (celular.getEstoque() >= quantidade) {
            celular.setEstoque(celular.getEstoque() - quantidade);
            System.out.println("Venda de " + quantidade + " unidade(s) de " + celular.getModelo() + " concluída.");
            return true;
        } else {
            System.out.println("Erro: Estoque insuficiente para " + celular.getModelo());
            return false;
        }
    }

    /**
     * Calcula o preço à vista aplicando um desconto fixo (10%).
     */
    public double calcularPrecoAVista(Celular celular) {
        double desconto = 0.10; // 10% de desconto
        return celular.getPreco() * (1 - desconto);
    }
}