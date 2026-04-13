package Servidor_java.Servicos;

import java.util.ArrayList;
import java.util.List;

import Servidor_java.Modelos.Celular;

public class CatalogoCelular {
    private List<Celular> listaDeCelulares;

    public CatalogoCelular() {
        this.listaDeCelulares = new ArrayList<>();
    }

    // Método de serviço: Adicionar um novo celular ao sistema
    public void adicionarCelular(Celular c) {
        listaDeCelulares.add(c);
        System.out.println("Serviço Catálogo: " + c.getModelo() + " adicionado.");
    }

    // Método de serviço: Buscar um celular específico pelo ID
    public Celular buscarPorId(int id) {
        for (Celular c : listaDeCelulares) {
            if (c.getId() == id) {
                return c;
            }
        }
        return null; // Caso não encontre
    }

    public void removerCelular(int id) {
        getTodos().removeIf(c -> c.getId() == id);
    }

    public List<Celular> getTodos() {
        return listaDeCelulares;
    }
}