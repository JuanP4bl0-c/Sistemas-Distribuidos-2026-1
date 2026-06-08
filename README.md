# Empresa de Venda de Aparelhos Telefônicos Sistemas Distribuidos 2026.1
Praticas e Trabalho em dupla feito com C++ como cliente e Java como servidor.

**Participantes:** Juan Pablo Rufino Mesquita (509982)  - Felipe Kauan dos Santos Silva  (510175)

## 1. Sobre o Projeto

**Resumo:** O servidor foi reimplementado como uma API HTTP leve usando a biblioteca embutida `com.sun.net.httpserver`. Ele expõe endpoints REST para gerenciar o catálogo de produtos e realizar vendas. Existe um cliente Python que consome essa API via `requests`. O cliente C++ local e o cliente CORBA permanecem no repositório como versões legadas/alternativas — o cliente C++ ativo está em outra máquina e, por solicitação, está sendo ignorado aqui.

## 2. Descrição do Projeto

- **Servidor:** implementado em `Servidor_java/Servidor.java`.
    - Endpoints expostos:
        - `GET /api/produtos` — lista todos os produtos.
        - `POST /api/produtos` — adiciona um produto.
        - `GET /api/produtos/{id}` — obtém produto por id.
        - `DELETE /api/produtos/{id}` — remove produto por id.
        - `POST /api/vendas` — realiza venda; aceita JSON com `produto_id`, `quantidade`, `vendedor_id` e `vendedor_nome`.

- **Lógica de negócio:** está em `ProdutoController.java` e em `Servidor_java/Servicos` — catálogo em memória, operações de listagem, busca, adição, remoção e venda.

- **Clientes:**
    - `Cliente_Python/cliente.py` — cliente que consome a API HTTP via `requests`.
        - Observação: a função `adicionar_produto` no script faz referência a `URL_BASE` em vez de `URL` — isso precisa ser corrigido antes de usar.
    - `Cliente_cpp/` — cliente C++ que usa sockets TCP e streams binários (versão legada; cliente funcional correto reside em outra máquina por orientação do autor).
    - Código CORBA em `Cliente_cpp/src/network` — middleware RMI-like mantido como legado.

**Conformidade com o requisito:**
- Requisito: "Comunicação cliente‑servidor via WS ou API. Não criar sockets ou RMI." 
- Situação atual: o **servidor HTTP** + **cliente Python** cumprem o requisito. Contudo, o repositório contém implementações **legadas** que usam sockets e CORBA; esses itens não cumprem o requisito se considerados parte do artefato final. Se o enunciado exige que todo código presente no repositório obedeça à restrição, então ainda há código não conforme.

## 3. Como executar a API HTTP

1. Compile as classes Java do servidor:

```bash
javac -cp .:json-20240303.jar Servidor_java/*.java Servidor_java/Modelos/*.java Servidor_java/Servicos/*.java
```

2. Execute o servidor HTTP:

```bash
java -cp .:json-20240303.jar Servidor_java.Servidor
```

3. Instale dependências e rode o cliente:

```bash
python3 -m pip install requests
python3 Cliente_Python/cliente.py
```

Observação: o `Cliente_Python/cliente.py` tem um pequeno bug em `adicionar_produto`. Trocar por `URL` ou ajustar a função antes de usar.


