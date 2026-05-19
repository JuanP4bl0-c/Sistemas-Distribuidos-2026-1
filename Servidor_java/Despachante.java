package Servidor_java;

import org.json.JSONObject;
import Servidor_java.Servicos.CatalogoProdutos;

public class Despachante {
    
    private EsqueletoCatalogo esqueleto;

    // O Despachante recebe a instância do catálogo real para passar ao esqueleto
    public Despachante(CatalogoProdutos catalogoReal) {
        this.esqueleto = new EsqueletoCatalogo(catalogoReal);
    }

    // Camada de GetRequest implícita: analisa o conteúdo estruturado do livro (Seção 5.2)
    public String selecionarEExecutar(String jsonRecebido) {
        try {
            JSONObject request = new JSONObject(jsonRecebido);
            
            // Lendo os metadados do envelope RPC (Figura 5.2 do livro)
            String objectReference = request.getString("objectReference");
            int methodId = request.getInt("methodId");
            
            // Captura os argumentos que serão processados pelo esqueleto
            JSONObject arguments = request.getJSONObject("arguments");

            // Verifica se a referência aponta para o nosso objeto remoto registrado
            if (objectReference.equals("CatalogoRemoto")) {
                return esqueleto.invocarMetodo(methodId, arguments);
            } else {
                return "{\"messageType\":1, \"arguments\": \"{\\\"status\\\": 404, \\\"msg\\\": \\\"Objeto remoto não encontrado.\\\"}\"}";
            }
        } catch (Exception e) {
            return "{\"messageType\":1, \"arguments\": \"{\\\"status\\\": 400, \\\"msg\\\": \\\"Erro no parsing do envelope RPC: " + e.getMessage() + "\\\"}\"}";
        }
    }
}