package Servidor_java;

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.*;

import Servidor_java.Modelos.*;
import Servidor_java.Servicos.ProdutoController;

import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

import com.sun.net.httpserver.*;



public class Servidor {
    private static final int PORTA = 8000;

    public static void main(String args[]) {

        Properties props = new Properties();
        
        try (InputStream in = Files.newInputStream(Path.of("Servidor_java","servidor.properties"))) {
                props.load(in);

                String host = props.getProperty("host");
                int porta = Integer.parseInt(props.getProperty("port", String.valueOf(PORTA)));

                ProdutoController controller = new ProdutoController();
                HttpServer server = HttpServer.create(new InetSocketAddress(host, porta), 0);
                server.createContext("/api/produtos", new ProdutoHandler(controller));
                server.createContext("/api/vendas", new ProdutoHandler(controller));
                server.setExecutor(null);
                server.start();

                System.out.println("\nServidor HTTP ativo: " + host + ":" + porta + "\n");
        } catch (Exception e) {
                System.err.println("Erro no servidor: " + e.getMessage());
                e.printStackTrace();
        }
    }

    private static class ProdutoHandler implements HttpHandler {

        private final ProdutoController controller;

        ProdutoHandler(ProdutoController controller) {
            this.controller = controller;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {

            try {
                String method = exchange.getRequestMethod();
                String path = exchange.getRequestURI().getPath();
                String[] segmentos = path.split("/");

                if ("/api/vendas".equals(path)) {
                    if ("POST".equalsIgnoreCase(method)) {
                        String corpo = lerCorpo(exchange.getRequestBody());
                        Map<String, String> dados = parseJsonObject(corpo);

                        // Extrai os dados do JSON recebido
                        int produtoId = parseInt(dados.get("produto_id"), 0);
                        int quantidade = parseInt(dados.get("quantidade"), 1);
                        String vendedorId = dados.getOrDefault("vendedor_id", "");
                        String vendedorNome = dados.getOrDefault("vendedor_nome", "");
                        
                        System.out.println("Recebida solicitação de venda: Produto ID=" + produtoId + ", Quantidade=" + quantidade + ", Vendedor ID=" + vendedorId + ", Vendedor Nome=" + vendedorNome);

                        // Cria o vendedor apenas se os dados foram enviados
                        Vendedor vendedor = null;
                        if (!vendedorId.isEmpty() && !vendedorNome.isEmpty()) {
                            vendedor = new Vendedor(vendedorId, vendedorNome);
                        }

                        // Tenta realizar a venda
                        Vendas resultadoVenda = controller.VenderProduto(produtoId, quantidade, vendedor);

                        if (resultadoVenda == null) {
                            responderJson(exchange, 400, mensagemErroJson(400, "Venda falhou. Produto não encontrado ou estoque insuficiente."));
                            System.out.println("Venda falhou para Produto ID=" + produtoId + ". Verifique se o produto existe e se há estoque suficiente.");
                            return;
                        }

                        // Se a venda deu certo, extraímos o resumo e enviamos para o cliente C++
                        String resumo = resultadoVenda.obterResumoVenda();
                        String jsonResposta = "{\"status\":200,\"mensagem\":\"Venda realizada com sucesso!\",\"resumo\":\"" + escapeJson(resumo) + "\"}";
                        
                        responderJson(exchange, 200, jsonResposta);

                        System.out.println(jsonResposta);
                        return;
                    }
                }


                if ("/api/produtos".equals(path)) {

                    System.out.println("Recebida solicitação para /api/produtos com método " + method);

                    if ("GET".equalsIgnoreCase(method)) {
                        responderJson(exchange, 200, listaParaJson(controller.listarTodos()));
                        System.out.println("Lista de produtos enviada para o cliente.");
                        return;
                    }

                    if ("POST".equalsIgnoreCase(method)) {
                        String corpo = lerCorpo(exchange.getRequestBody());
                        Produto produto = produtoFromJson(corpo);
                        controller.adicionarProduto(produto);

                        responderJson(exchange, 201, respostaProdutoJson(201, "Produto adicionado com sucesso via API!", produto));
                        System.out.println("Produto adicionado via API: " + produto);
                        return;
                    }
                }

                if (segmentos.length == 4 && "api".equals(segmentos[1]) && "produtos".equals(segmentos[2])) {
                    int id = Integer.parseInt(segmentos[3]);

                    if ("GET".equalsIgnoreCase(method)) {
                        Produto produto = controller.buscarPorId(id);
                        if (produto == null) {
                            responderJson(exchange, 404, mensagemErroJson(404, "Produto não encontrado."));
                            return;
                        }
                        responderJson(exchange, 200, produtoParaJson(produto));
                        return;
                    }

                    if ("DELETE".equalsIgnoreCase(method)) {
                        boolean removido = controller.removerProduto(id);
                        if (!removido) {
                            responderJson(exchange, 404, mensagemErroJson(404, "Produto não encontrado para remoção."));
                            return;
                        }

                        responderJson(exchange, 200, mensagemOkJson(200, "Produto removido."));
                        return;
                    }
                }

                responderJson(exchange, 405, mensagemErroJson(405, "Método não permitido."));

            } catch (NumberFormatException e) {
                responderJson(exchange, 400, mensagemErroJson(400, "ID inválido na URL."));
            } catch (Exception e) {
                responderJson(exchange, 500, mensagemErroJson(500, "Erro interno: " + e.getMessage()));
            } finally {
                exchange.close();
            }
        }

        private static String lerCorpo(InputStream inputStream) throws IOException {
            return new String(inputStream.readAllBytes(), StandardCharsets.UTF_8);
        }

        private static void responderJson(HttpExchange exchange, int status, String corpo) throws IOException {
            byte[] bytes = corpo.getBytes(StandardCharsets.UTF_8);
            exchange.getResponseHeaders().set("Content-Type", "application/json; charset=UTF-8");
            exchange.sendResponseHeaders(status, bytes.length);
            try (OutputStream outputStream = exchange.getResponseBody()) {
                outputStream.write(bytes);
            }
        }

        private static String mensagemErroJson(int status, String message) {
            return "{\"status\":" + status + ",\"message\":\"" + escapeJson(message) + "\"}";
        }

        private static String mensagemOkJson(int status, String message) {
            return "{\"status\":" + status + ",\"message\":\"" + escapeJson(message) + "\"}";
        }

        private static String respostaProdutoJson(int status, String message, Produto produto) {
            return "{\"status\":" + status + ",\"message\":\"" + escapeJson(message) + "\",\"produto\":" + produtoParaJson(produto) + "}";
        }

        private static String listaParaJson(List<Produto> produtos) {
            StringBuilder builder = new StringBuilder();
            builder.append("[");
            for (int i = 0; i < produtos.size(); i++) {
                if (i > 0) {
                    builder.append(",");
                }
                builder.append(produtoParaJson(produtos.get(i)));
            }
            builder.append("]");
            return builder.toString();
        }

        private static String produtoParaJson(Produto produto) {
            StringBuilder builder = new StringBuilder();
            builder.append("{");
            builder.append("\"tipo\":\"").append(escapeJson(produto.getTipo())).append("\"");
            builder.append(",\"id\":").append(produto.getId());
            builder.append(",\"nome\":\"").append(escapeJson(produto.getNome())).append("\"");
            builder.append(",\"descricao\":\"").append(escapeJson(produto.getDescricao())).append("\"");
            builder.append(",\"preco\":").append(produto.getPreco());
            builder.append(",\"estoque\":").append(produto.getEstoque());

            if (produto instanceof Celular celular) {
                builder.append(",\"marca\":\"").append(escapeJson(celular.getMarca())).append("\"");
                builder.append(",\"modelo\":\"").append(escapeJson(celular.getModelo())).append("\"");
            } else if (produto instanceof Capa capa) {
                builder.append(",\"modelo\":\"").append(escapeJson(capa.getModelo())).append("\"");
                builder.append(",\"material\":\"").append(escapeJson(capa.getMaterial())).append("\"");
            } else if (produto instanceof Pelicula pelicula) {
                builder.append(",\"modelo\":\"").append(escapeJson(pelicula.getModelo())).append("\"");
                builder.append(",\"material\":\"").append(escapeJson(pelicula.getMaterial())).append("\"");
            } else if (produto instanceof PowerBank powerBank) {
                builder.append(",\"marca\":\"").append(escapeJson(powerBank.getMarca())).append("\"");
                builder.append(",\"modelo\":\"").append(escapeJson(powerBank.getModelo())).append("\"");
                builder.append(",\"capacidade\":").append(powerBank.getcapacidade());
            }

            builder.append("}");
            return builder.toString();
        }

        private static Produto produtoFromJson(String corpo) {
            Map<String, String> dados = parseJsonObject(corpo);
            String tipo = dados.getOrDefault("tipo", "Produto");
            int id = parseInt(dados.get("id"), 0);
            String nome = dados.getOrDefault("nome", "");
            String descricao = dados.getOrDefault("descricao", "");
            double preco = parseDouble(dados.get("preco"), 0.0);
            int estoque = parseInt(dados.get("estoque"), 0);

            return switch (tipo) {
                case "Celular" -> new Celular(id, nome, descricao, preco, estoque, dados.getOrDefault("marca", ""), dados.getOrDefault("modelo", ""));
                case "Capa" -> new Capa(id, nome, descricao, preco, estoque, dados.getOrDefault("modelo", ""), dados.getOrDefault("material", ""));
                case "Pelicula" -> new Pelicula(id, nome, descricao, preco, estoque, dados.getOrDefault("modelo", ""), dados.getOrDefault("material", ""));
                case "PowerBank" -> new PowerBank(id, nome, descricao, preco, estoque, dados.getOrDefault("marca", ""), dados.getOrDefault("modelo", ""), parseInt(dados.get("capacidade"), 0));
                default -> new Produto(id, nome, descricao, preco, estoque);
            };
        }

        private static Map<String, String> parseJsonObject(String corpo) {
            Map<String, String> dados = new HashMap<>();
            String texto = corpo == null ? "" : corpo.trim();
            if (texto.startsWith("{")) {
                texto = texto.substring(1);
            }
            if (texto.endsWith("}")) {
                texto = texto.substring(0, texto.length() - 1);
            }

            Pattern pattern = Pattern.compile("\"([^\"]+)\"\\s*:\\s*(\"((?:\\\\.|[^\"])*)\"|[-]?[0-9]+(?:\\.[0-9]+)?|true|false|null)");
            Matcher matcher = pattern.matcher(texto);
            while (matcher.find()) {
                String chave = matcher.group(1);
                String valorBruto = matcher.group(2);
                if (valorBruto.startsWith("\"")) {
                    dados.put(chave, unescapeJson(valorBruto.substring(1, valorBruto.length() - 1)));
                } else if (!"null".equals(valorBruto)) {
                    dados.put(chave, valorBruto);
                }
            }

            return dados;
        }

        private static String escapeJson(String valor) {
            if (valor == null) {
                return "";
            }
            return valor
                    .replace("\\", "\\\\")
                    .replace("\"", "\\\"")
                    .replace("\n", "\\n")
                    .replace("\r", "\\r")
                    .replace("\t", "\\t");
        }

        private static String unescapeJson(String valor) {
            return valor
                    .replace("\\n", "\n")
                    .replace("\\r", "\r")
                    .replace("\\t", "\t")
                    .replace("\\\"", "\"")
                    .replace("\\\\", "\\");
        }

        private static int parseInt(String valor, int padrao) {
            try {
                return valor == null ? padrao : Integer.parseInt(valor);
            } catch (NumberFormatException e) {
                return padrao;
            }
        }

        private static double parseDouble(String valor, double padrao) {
            try {
                return valor == null ? padrao : Double.parseDouble(valor);
            } catch (NumberFormatException e) {
                return padrao;
            }
        }
    }
}