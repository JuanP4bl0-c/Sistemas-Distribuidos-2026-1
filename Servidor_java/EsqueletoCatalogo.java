package Servidor_java;

import org.json.JSONArray;
import org.json.JSONObject;
import Servidor_java.Modelos.*;
import Servidor_java.Servicos.CatalogoProdutos;

/**
 * EsqueletoCatalogo: camada "esqueleto" do RPC/Dispatcher.
 *
 * Recebe requisições (identificadas por um methodID e argumentos em JSON),
 * delega a execução para o objeto local `CatalogoProdutos` e monta uma
 * resposta JSON padronizada com código de status e payload.
 */
public class EsqueletoCatalogo {

    private CatalogoProdutos catalogoReal;

    public EsqueletoCatalogo(CatalogoProdutos catalogoReal) {
        this.catalogoReal = catalogoReal;
    }

    /**
     * Invoca um método do catálogo com base em um identificador inteiro.
     *
     * @param methodID id numérico do método remoto (ex.: 1=listar, 2=adicionar,...)
     * @param arguments argumentos codificados como JSONObject (parâmetros do método)
     * @return resposta serializada em String JSON com ao menos um campo `status`.
     */
    public String invocarMetodo(int methodID, JSONObject arguments) {
        JSONObject respostaJson = new JSONObject();

        try {
            switch (methodID) {
                case 1: // LISTAR: retorna lista de todos os produtos
                    System.out.println("Esqueleto executando localmente: Listar");
                    JSONArray lista = new JSONArray();

                    // Converte cada Produto local para um JSONObject simples
                    for (Produto p : catalogoReal.getTodos()) {
                        JSONObject prodJson = new JSONObject();
                        prodJson.put("id", p.getId());
                        prodJson.put("nome", p.getNome());
                        prodJson.put("descricao", p.getDescricao());
                        prodJson.put("preco", p.getPreco());
                        prodJson.put("quantidade", p.getEstoque());
                        lista.put(prodJson);
                    }

                    respostaJson.put("status", 200);
                    respostaJson.put("dados", lista);
                    break;

                case 2: // ADICIONAR: cria e adiciona um produto conforme 'tipo' no JSON
                    System.out.println("Esqueleto executando localmente: Adicionar");
                    String tipo = arguments.getString("tipo");
                    int id = arguments.getInt("id");
                    String nome = arguments.getString("nome");
                    String desc = arguments.getString("descricao");
                    double preco = arguments.getDouble("preco");
                    int qtd = arguments.getInt("quantidade");

                    // Exemplo: cria instância correta conforme campo `tipo`
                    if (tipo.equalsIgnoreCase("Celular")) {
                        String marca = arguments.getString("marca");
                        String modelo = arguments.getString("modelo");
                        catalogoReal.AdicionarProduto(new Celular(id, nome, desc, preco, qtd, marca, modelo));
                    } else if (tipo.equalsIgnoreCase("Capa")) {
                        String modCelular = arguments.getString("modeloCelular");
                        String material = arguments.getString("material");
                        catalogoReal.AdicionarProduto(new Capa(id, nome, desc, preco, qtd, modCelular, material));
                    }
                    // Observação: ainda faltam as ramas para Pelicula e PowerBank

                    respostaJson.put("status", 200);
                    respostaJson.put("msg", "Produto adicionado com sucesso por valor!");
                    break;

                case 3: // REMOVER: remove produto por id
                    System.out.println("Esqueleto executando localmente: Remover");
                    int idRemover = arguments.getInt("id");
                    catalogoReal.RemoverProduto(idRemover);

                    respostaJson.put("status", 200);
                    respostaJson.put("msg", "Produto removido se existia.");
                    break;

                case 4: // BUSCAR: retorna dados básicos do produto solicitado
                    System.out.println("Esqueleto executando localmente: Buscar");
                    int idBuscar = arguments.getInt("id");
                    Produto encontrado = catalogoReal.GetProduto(idBuscar);

                    if (encontrado != null) {
                        respostaJson.put("status", 200);
                        respostaJson.put("id", encontrado.getId());
                        respostaJson.put("nome", encontrado.getNome());
                        respostaJson.put("preco", encontrado.getPreco());
                    } else {
                        respostaJson.put("status", 404);
                        respostaJson.put("msg", "Produto não encontrado.");
                    }
                    break;

                default:
                    respostaJson.put("status", 405);
                    respostaJson.put("msg", "Método ID não suportado.");
            }
        } catch (Exception e) {
            // Em caso de qualquer erro (chave faltando no JSON, cast inválido, etc.)
            // retornamos status 500 com mensagem curta — para debugging local.
            respostaJson.put("status", 500);
            respostaJson.put("msg", "Erro interno no esqueleto: " + e.getMessage());
        }

        return respostaJson.toString();
    }
}