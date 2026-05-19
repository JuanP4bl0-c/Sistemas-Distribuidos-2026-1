package Servidor_java.Servicos;

import java.util.ArrayList;
import java.util.List;

import Servidor_java.Modelos.Celular;

/**
 * Catálogo especializado para `Celular`.
 * Contém operações específicas (adicionar, buscar, remover) para a coleção
 * de objetos `Celular` do sistema.
 */
public class CatalogoCelular {
    private List<Celular> listaDeCelulares;

    public CatalogoCelular() {
        this.listaDeCelulares = new ArrayList<>();
    }

    /**
     * Serviço: adiciona um novo celular ao catálogo dedicado.
     */
    public void adicionarCelular(Celular c) {
        listaDeCelulares.add(c);
        System.out.println("Serviço Catálogo: " + c.getModelo() + " adicionado.");
    }

    /**
     * Serviço: busca por ID; retorna `null` se não encontrado.
     */
    public Celular buscarPorId(int id) {
        for (Celular c : listaDeCelulares) {
            if (c.getId() == id) {
                return c;
            }
        }
        return null;
    }

    /**
     * Remove celular por ID.
     */
    public void removerCelular(int id) {
        getTodos().removeIf(c -> c.getId() == id);
    }

    /**
     * Retorna todos os celulares registrados.
     */
    public List<Celular> getTodos() {
        return listaDeCelulares;
    }
}