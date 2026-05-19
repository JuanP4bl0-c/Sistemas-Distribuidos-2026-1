# Empresa de Venda de Aparelhos Telefônicos Sistemas Distribuidos 2026.1
Praticas e Trabalho em dupla feito com C++ como cliente e Java como servidor.

**Participantes:** Juan Pablo Rufino Mesquita (509982)  - Felipe Kauan dos Santos Silva  (510175)

## 1. Sobre o Projeto

Aplicação de Invocação Remota em projeto de E-commerce de Aparelhos Celulares e acessórios. O projeto utiliza o middleware CORBA para viabilizar a interoperabilidade cross-language nativa, permitindo que um cliente construído em C++ interaja diretamente com um servidor implementado em Java, sem a criação manual de sockets de transporte.

## 2. Descrição do Projeto

Este projeto de um sistema distribuído de catálogo de produtos visa consolidar e demonstrar os conhecimentos práticos sobre Invocação Remota de Métodos e Representação Externa de Dados, onde é utilizado por pacotes estruturados no formato JSON.

O projeto implementa um e-commerce de aparelhos celulares e acessórios, onde:

- O **servidor** Gerencia o catálogo em memória. A infraestrutura foi totalmente estendida com:

    Esqueleto (Skeleton): Realiza o Unmarshalling (desempacotamento) do JSON interno recebido do C++, processa a lógica de negócio por valor nas entidades locais, executa a ação sobre o catálogo real e devolve a resposta no fluxo do método simulando o sendReply().

    ServidorCatalogoImpl (Gerenciador do ORB): Captura os bytes do middleware, simulando o comportamento de getRequest(), expõe as mensagens no console e invoca os subsistemas de tratamento.

    Despachante (Dispatcher): Analisa o envelope RPC, lê as propriedades textuais (objectReference, methodId) e roteia a requisição para o esqueleto correto.

    - O **cliente** 

    O Cliente (C++): Fornece uma interface em modo texto (Menu) que permite realizar operações no catálogo. Ele envelopa os dados na estrutura de uma Mensagem RPC baseada na Figura 5.2 do livro (contendo messageType, requestId, objectReference, methodId e arguments), converte o conteúdo em bytes nativos (CatalogoApp::ByteArray) e dispara a chamada através do Stub do CORBA.

    O Middleware (CORBA): Atua como o protocolo de requisição-resposta subjacente. Ele resolve referências via Serviço de Nomes Transiente (tnameserv) e realiza o transporte de rede e o roteamento dos dados sem o uso de sockets manuais.



## 3. Como Executar

### 3.1 Executar o CORBA:

/usr/lib/jvm/java-8-openjdk-amd64/bin/java -Dcom.sun.CORBA.ORBServerHost=192.168.0.6 com.sun.corba.se.impl.naming.cosnaming.TransientNameServer -ORBInitialPort 1050

### 3.2 Executar o Cliente: 

./bin/cliente -ORBInitRef NameService=corbaloc:iiop:192.168.0.6:1050/NameService

### 3.3 Executar o Servidor:

/usr/lib/jvm/java-8-openjdk-amd64/bin/javac -cp .:json-20240303.jar Servidor_java/*.java CatalogoApp/*.java Servidor_java/Modelos/*.java Servidor_java/Servicos/*.java

/usr/lib/jvm/java-8-openjdk-amd64/bin/java -Dcom.sun.CORBA.ORBServerHost=192.168.0.6 -cp .:json-20240303.jar Servidor_java.Servidor -ORBInitialPort 1050 -ORBInitialHost 192.168.0.6
