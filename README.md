# Empresa de Venda de Aparelhos Telefônicos Sistemas Distribuidos 2026.1
Praticas e Trabalho em dupla feito com C++ como cliente e Java como servidor.

**Participantes:** Juan Pablo Rufino Mesquita (509982)  - Felipe Kauan dos Santos Silva  (510175)

## 1. Sobre o Projeto

Implementação de projeto de E-comerce de Aparelhos Celulares e acessórios, onde é trabalhado com serialização de Pojos de Porodutos e aplicação de requrst/reply em coneção TCP

## 2. Descrição do Projeto

Este Projeto de um sistema distribuído de catálogo de produtos utilizando uma arquitetura Cliente-Servidor com objetivo central de demonstrar a comunicação entre tecnologias distintas onde o servidor é Java e o cliente é C++, onde é utilizado sockets TCP. É também trabalhado com os desafios inerentes à comunicação em rede, como a serialização de dados e a compatibilidade de arquitetura.

O projeto implementa um e-commerce de aparelhos celulares e acessórios, onde:

- O **servidor** gerencia o catálogo de produtos, estoque e processamento de requisições,onde ao conectar com o cliente, consegue receber multipos produtos por inputstream. Ao encerrar o serviodr, é salvo um arquivo chamado "catalogo.csv" onde contem todos os dados do catalogo de produtos.

- O **cliente** Faz uma requisição de inserir uma stream de vetos de varios produtos distintos.


## 3. Como Executar

### 3.1 Servidor Java

    javac -d . *.java Modelos/*.java Serializacao/*.java Servicos/*.java Stream/*.java Utils/*.java

Atenção, o servidor java utiliza de um aquivo que não foi enviado no git chamado config.properties, onde possui informações como o Ip local da maquina e da porta. para criar um para sua maquina procure pelo seu ip e insira nesse formado de arquivo:

    server.host=0.0.0.0
    server.porta=5001

### 3.2 Cliente C++
    
    make clean
    make cliente
    ./bin/cliente

Edite o Config.txt para o Ip do seu servidor:

    SERVER_IP=127.0.0.1
    SERVER_PORT=8888
