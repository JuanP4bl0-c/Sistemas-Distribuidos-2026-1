# API TCP - Servidor de E-commerce

## 🚀 Como Usar

### Iniciar o Servidor
```bash
cd Servidor_py
python3 server.py
```

Saída esperada:
```
============================================================
Servidor TCP iniciado na porta 5000
============================================================
Aguardando conexões...
============================================================
```

### Testar com Cliente Python
```bash
python3 cliente_tcp.py
```

---

## 📋 Protocolo TCP

**Host:** `localhost`  
**Porta:** `5000`  
**Formato:** Comandos em texto + resposta em JSON

---

## 🎯 Comandos Disponíveis

### PRODUTOS

#### 1. Listar todos os produtos
```
Comando: LISTAR_PRODUTOS
Resposta: {"status": "sucesso", "dados": [{...}, {...}]}
```

#### 2. Buscar produto por ID
```
Comando: GET_PRODUTO:1
Resposta: {"status": "sucesso", "dados": {"id": 1, "nome": "...", "preco": 3500.0, ...}}
```

#### 3. Criar novo produto
```
Comando: CRIAR_PRODUTO:nome:descricao:preco:estoque
Exemplo: CRIAR_PRODUTO:Teclado:Mecânico:250.0:30
Resposta: {"status": "sucesso", "dados": {"id": 4, ...}}
```

#### 4. Atualizar estoque
```
Comando: ATUALIZAR_ESTOQUE:id:quantidade
Exemplo: ATUALIZAR_ESTOQUE:1:100
Resposta: {"status": "sucesso", "dados": {"id": 1, "estoque": 100, ...}}
```

---

### CLIENTES

#### 1. Listar todos os clientes
```
Comando: LISTAR_CLIENTES
Resposta: {"status": "sucesso", "dados": [{...}, {...}]}
```

#### 2. Buscar cliente por ID
```
Comando: GET_CLIENTE:1
Resposta: {"status": "sucesso", "dados": {"id": 1, "nome": "...", "email": "...", ...}}
```

#### 3. Registrar novo cliente
```
Comando: REGISTRAR_CLIENTE:nome:email:telefone:endereco
Exemplo: REGISTRAR_CLIENTE:Pedro Silva:pedro@email.com:11987654321:Rua C, 789
Resposta: {"status": "sucesso", "dados": {"id": 3, ...}}
```

---

### PEDIDOS

#### 1. Listar todos os pedidos
```
Comando: LISTAR_PEDIDOS
Resposta: {"status": "sucesso", "dados": [{...}, {...}]}
```

#### 2. Buscar pedido por ID
```
Comando: GET_PEDIDO:1
Resposta: {"status": "sucesso", "dados": {"id": 1, "cliente_id": 1, "produtos_ids": [1, 2], ...}}
```

#### 3. Criar novo pedido
```
Comando: CRIAR_PEDIDO:cliente_id:produtos_ids:total
Exemplo: CRIAR_PEDIDO:1:1,2,3:3815.0
Resposta: {"status": "sucesso", "dados": {"id": 3, "status": "Pendente", ...}}
```

#### 4. Atualizar status do pedido
```
Comando: ATUALIZAR_STATUS_PEDIDO:id:status
Exemplo: ATUALIZAR_STATUS_PEDIDO:1:Entregue
Resposta: {"status": "sucesso", "dados": {"id": 1, "status": "Entregue", ...}}
```

---

## 💻 Exemplo de Cliente C++

```cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Criar socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Erro ao criar socket" << std::endl;
        return 1;
    }
    
    // Conectar ao servidor
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Erro ao conectar" << std::endl;
        return 1;
    }
    
    std::cout << "✓ Conectado ao servidor" << std::endl;
    
    // Enviar comando
    std::string comando = "LISTAR_PRODUTOS";
    send(sock, comando.c_str(), comando.length(), 0);
    
    // Receber resposta
    char buffer[4096] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    
    std::cout << "Resposta: " << buffer << std::endl;
    
    // Fechar conexão
    close(sock);
    return 0;
}
```

**Compilar:**
```bash
g++ cliente.cpp -o cliente
./cliente
```

---

## 📊 Exemplo de Resposta JSON

```json
{
  "status": "sucesso",
  "dados": [
    {
      "id": 1,
      "nome": "Notebook",
      "descricao": "Dell 15 polegadas",
      "preco": 3500.0,
      "estoque": 10
    },
    {
      "id": 2,
      "nome": "Mouse",
      "descricao": "Logitech sem fio",
      "preco": 50.0,
      "estoque": 100
    }
  ]
}
```

---

## ⚠️ Tratamento de Erros

Se algo der errado:
```json
{
  "status": "erro",
  "mensagem": "Produto não encontrado"
}
```

---

## 🔄 Fluxo Típico

1. **Cliente se conecta** → `socket.connect(localhost:5000)`
2. **Envia comando** → `"GET_PRODUTO:1"`
3. **Servidor processa** → Busca no banco de dados
4. **Envia resposta** → JSON com dados ou erro
5. **Cliente processa** → Parse JSON e usa dados
6. **Desconecta** → `socket.close()`

---

## ✅ Vantagens desta Abordagem

✓ Simples e direto  
✓ Sem dependências externas  
✓ Rápido e eficiente  
✓ Fácil debugar (JSON é legível)  
✓ Funciona em qualquer linguagem  
✓ Sem complicações de serialização  
