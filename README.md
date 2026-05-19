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


Executar o CORBA:

/usr/lib/jvm/java-8-openjdk-amd64/bin/java -Dcom.sun.CORBA.ORBServerHost=192.168.0.6 com.sun.corba.se.impl.naming.cosnaming.TransientNameServer -ORBInitialPort 1050


 executar o Servidor:
 /usr/lib/jvm/java-8-openjdk-amd64/bin/javac -cp .:json-20240303.jar Servidor_java/*.java CatalogoApp/*.java Servidor_java/Modelos/*.java Servidor_java/Servicos/*.java

 /usr/lib/jvm/java-8-openjdk-amd64/bin/java -Dcom.sun.CORBA.ORBServerHost=192.168.0.6 -cp .:json-20240303.jar Servidor_java.Servidor -ORBInitialPort 1050 -ORBInitialHost 192.168.0.6
