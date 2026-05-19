#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"
#include "utils/Config.h"

// ➔ Novas camadas organizadas de infraestrutura e protocolos
#include "network/CORBA_Client.h"
#include "protocols/CatalogoStub.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>

void exibirErro(const std::string& msg) {
    std::cerr << "\n[ERRO] " << msg << "\n";
}

int main(int argc, char** argv) {
    try {
        Config config("config/Config.txt");

        // 1. Inicializa a camada de transporte CORBA
        CorbaClient client(argc, argv, "CatalogoRemoto");

        if (!client.isConnected()) {
            exibirErro("Falha crítica: Cliente C++ não conseguiu se conectar ao NameService.");
            return 1;
        }

        // 2. Instancia o Stub (Proxy) injetando a rede CORBA nele
        // A partir daqui, o main conversa APENAS com o stub!
        CatalogoStub stub(client, "CatalogoRemoto");

        bool rodando = true;
        while (rodando) {
            std::cout << "\n========================================\n";
            std::cout << "        MENU CATALOGO CORBA (C++)       \n";
            std::cout << "========================================\n";
            std::cout << "1. Listar Produtos do Catalogo\n";
            std::cout << "2. Adicionar Carga de Teste (Produtos)\n";
            std::cout << "3. Remover Produto por ID\n";
            std::cout << "0. Sair\n";
            std::cout << "Escolha uma opcao: ";
            
            int opcao;
            std::cin >> opcao;

            switch (opcao) {
                case 1: {
                    std::cout << "\n[Enviando] Solicitando listagem do catalogo...\n";
                    
                    // O Stub executa a chamada, captura o JSON do Java e já imprime na tela!
                    stub.listarProdutos(); 
                    
                    std::cout << "\n========================================\n";
                    break;
                }
                
                case 2: {
                    std::cout << "\n[Enviando] Preparando carga de produtos para cadastro...\n";
                    
                    std::vector<std::shared_ptr<Produto>> lista = {
                        std::make_shared<Celular>(1, "IPhone 15", "Apple celular", 5000.0, 5, "Apple", "15 Pro"),
                        std::make_shared<Capa>(2, "Capa Iphone", "Capa azul", 15.0, 20, "Iphone 15", "Plastico"),
                        std::make_shared<Pelicula>(3, "Pelicula", "5 polegadas", 25.50, 15, "Iphone 15", "Vidro"),
                        std::make_shared<PowerBank>(4, "Power Bank", "Bateria", 200.0, 10, "Xiaomi", "10000mAh", 1000)
                    };

                    // O Stub engole a lista de produtos, empacota e devolve a String de status limpa
                    std::string resultado = stub.adicionarProdutos(lista);
                    std::cout << "\n>>> [Status do Servidor]: " << resultado << "\n";
                    break;
                }
                
                case 3: {
                    std::cout << "\nDigite o ID do produto que deseja remover: ";
                    int idRemover;
                    std::cin >> idRemover;

                    std::cout << "[Enviando] Solicitando exclusao do ID " << idRemover << "...\n";

                    // Chamada transparente passando o ID puro
                    std::string resultado = stub.removerProduto(idRemover);
                    std::cout << "\n>>> [Status do Servidor]: " << resultado << "\n";
                    break;
                }
                
                case 0:
                    std::cout << "\nEncerrando o cliente CORBA. Ate logo!\n";
                    rodando = false;
                    break;
                
                default:
                    exibirErro("Opcao invalida! Tente novamente.");
                    break;
            }
        }
    }
    catch (const std::exception& e) {
        exibirErro(std::string("Erro Inesperado: ") + e.what());
        return 1;
    }

    return 0;
}