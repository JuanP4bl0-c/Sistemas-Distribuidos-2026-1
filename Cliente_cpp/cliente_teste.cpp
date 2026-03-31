#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ClienteProduto {

private:
    int socket_fd;
    const char* host;
    int porta;

public:
    ClienteProduto(const char* h = "0.0.0.0", int p = 5001):socket_fd(-1), host(h), porta(p) {}  // Ordem corrigida!

    bool conectar() {
        // Criar socket
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            std::cerr << "✗ Erro ao criar socket" << std::endl;
            return false;
        }

        // Conectar ao servidor
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(porta);
        
        if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
            std::cerr << "✗ Endereço inválido" << std::endl;
            return false;
        }

        if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "✗ Erro ao conectar ao servidor em " << host << ":" << porta << std::endl;
            return false;
        }

        std::cout << "✓ Conectado ao servidor " << host << ":" << porta << std::endl;
        return true;
    }

    std::string enviar_comando(const std::string& comando) {
        if (socket_fd < 0) {
            std::cerr << "✗ Não conectado" << std::endl;
            return "";
        }

        // Enviar comando
        std::cout << "→ Enviando: " << comando << std::endl;
        if (send(socket_fd, comando.c_str(), comando.length(), 0) < 0) {
            std::cerr << "✗ Erro ao enviar comando" << std::endl;
            return "";
        }

        // Receber resposta (aumentado para 8KB)
        char buffer[8192] = {0};
        int n = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
        if (n < 0) {
            std::cerr << "✗ Erro ao receber resposta" << std::endl;
            return "";
        }

        if (n == 0) {
            std::cerr << "✗ Conexão fechada pelo servidor" << std::endl;
            return "";
        }

        buffer[n] = '\0';
        std::cout << "← Recebido " << n << " bytes" << std::endl;
        return std::string(buffer);
    }

    void desconectar() {
        if (socket_fd >= 0) {
            close(socket_fd);
            socket_fd = -1;
            std::cout << "✓ Desconectado" << std::endl;
        }
    }

    ~ClienteProduto() {
        desconectar();
    }

    // ==================== MÉTODOS DE REQUISIÇÃO ====================

    void listar_produtos() {
        try {
            std::string resposta = enviar_comando("LISTAR_PRODUTOS");
            if (resposta.empty()) return;
            
            json resp = json::parse(resposta);
            std::cout << resp.dump(2) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "✗ Erro ao parsear JSON: " << e.what() << std::endl;
        }
    }

    void get_produto(int id) {
        try {
            std::string comando = "GET_PRODUTO:" + std::to_string(id);
            std::string resposta = enviar_comando(comando);
            if (resposta.empty()) return;
            
            json resp = json::parse(resposta);
            std::cout << resp.dump(2) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "✗ Erro ao parsear JSON: " << e.what() << std::endl;
        }
    }

    void atualizar_estoque(int id, int quantidade) {
        try {
            std::string comando = "ATUALIZAR_ESTOQUE:" + std::to_string(id) + "," + std::to_string(quantidade);
            std::string resposta = enviar_comando(comando);
            if (resposta.empty()) return;
            
            json resp = json::parse(resposta);
            std::cout << resp.dump(2) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "✗ Erro ao parsear JSON: " << e.what() << std::endl;
        }
    }
};

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    ClienteProduto cliente;

    if (!cliente.conectar()) {
        return 1;
    }

    while (true)
    {
        std::cout << "\nComandos disponíveis:\n1. Listar produtos\n2. Buscar produto por ID\n3. Atualizar estoque\n4. Sair\nEscolha uma opção: ";
        int opcao;
        std::cin >> opcao;

        if (opcao == 1) {
            
            cliente.listar_produtos();
            
        } else if (opcao == 2) {
            
            std::cout << "Digite o ID do produto: ";
            int id;
            std::cin >> id;
            cliente.get_produto(id);

        } else if (opcao == 3) {
            
            std::cout << "Digite o ID do produto: ";
            int id;
            std::cin >> id;
            std::cout << "Digite a nova quantidade em estoque: ";
            int quantidade;
            std::cin >> quantidade;
            cliente.atualizar_estoque(id, quantidade);


        } else if (opcao == 4) {
            break;
        } else {
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    }
    

    cliente.desconectar();
    return 0;
}