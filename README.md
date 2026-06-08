# Empresa de Venda de Aparelhos Telefônicos Sistemas Distribuidos 2026.1
Praticas e Trabalho em dupla feito com C++ e Python como cliente e Java como servidor.

**Participantes:** Juan Pablo Rufino Mesquita (509982)  - Felipe Kauan dos Santos Silva  (510175)

## 1. Sobre o Projeto

**Resumo:** O servidor foi reimplementado como uma API HTTP usando a biblioteca embutida `com.sun.net.httpserver`. Ele expõe endpoints REST para gerenciar o catálogo de produtos e realizar vendas.

Existe clientes feitos com a linguagem Python e C++ que consome essa API via `requests`.

## 2. Descrição do Projeto

- **Servidor:** implementado em `Servidor_java/Servidor.java`.
    - O servidor possui seguintes endpoints expostos:
        - `GET /api/produtos` — lista todos os produtos.
        - `POST /api/produtos` — adiciona um produto.
        - `GET /api/produtos/{id}` — obtém produto por id.
        - `DELETE /api/produtos/{id}` — remove produto por id.
        - `POST /api/vendas` — realiza venda; aceita JSON com `produto_id`, `quantidade`, `vendedor_id` e `vendedor_nome` respectivamente.

- **Lógica de negócio:** está em `ProdutoController.java` e em `Servidor_java/Servicos` — operações de listagem, busca, adição, remoção e venda.

- **Clientes:**
    - `Cliente C++` — cliente que consome a API HTTP via `requests`.
    - `Cliente Python` — cliente que consome a API HTTP via `requests`, criado em seguida do cliente_cpp, possuindo as mesmas funcionalidades aplicadas.


## 3. Como executar a API HTTP

1. Compile as classes Java do servidor:

```bash
javac $(find Servidor_java -name '*.java' | sort)
java -cp Servidor_java:. Servidor_java.Servidor
```

2. Instale dependências e rode o cliente Python:

```bash
python3 -m pip install requests
python3 Cliente_Python/cliente.py
```


