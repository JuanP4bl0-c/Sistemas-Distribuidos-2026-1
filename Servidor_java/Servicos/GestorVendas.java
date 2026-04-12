package Servidor_java.Servicos;

import Servidor_java.Modelos.Celular;


public class GestorVendas {

    // Método de serviço: Processar uma venda
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

    // Método de serviço: Aplicar desconto para pagamentos à vista
    public double calcularPrecoAVista(Celular celular) {
        double desconto = 0.10; // 10% de desconto
        return celular.getPreco() * (1 - desconto);
    }
}