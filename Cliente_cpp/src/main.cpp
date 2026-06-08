<<<<<<< Updated upstream
#include "modelos/Produto.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"
<<<<<<< HEAD
#include "utils/Config.h"

// Camadas de infraestrutura e protocolos (transporte e stub de negócio)
#include "network/CORBA_Client.h"
#include "protocols/CatalogoStub.h"

=======
>>>>>>> Stashed changes
#include <iostream>
#include <memory>
#include <string> // Necessário para std::getline
#include "produtoAPI.h" 
#include "modelos/Vendedor.h"

// Função auxiliar para realizar o login
std::shared_ptr<Vendedor> realizarLogin() {
    std::string nome, vendid;
    std::cout << "\n=== LOGIN DE GESTOR ===" << std::endl;
    std::cout << "Nome do Gestor: ";
    std::getline(std::cin, nome);
    std::cout << "ID do Gestor: ";
    std::getline(std::cin, vendid);
    
    // Retorna um Vendedor validado (ou você pode adicionar lógica de verificação aqui)
    return std::make_shared<Vendedor>(nome, vendid);
}

int main() {
    ProdutoAPI api;

    // 1. Validação inicial: O programa não segue se o login não ocorrer
    auto gestorAtual = realizarLogin();

    std::cout << "\n=====================================\n";
    std::cout << " BEM-VINDO AO SISTEMA DE VENDAS\n";
    std::cout << " Gestor autenticado: " << gestorAtual->nome << " (ID: " << gestorAtual->id << ")\n";
    std::cout << "=====================================\n";
    
    int opcao;
    do {
        std::cout << "\n=== MENU DO CLIENTE C++ ===" << std::endl;
        std::cout << "1. Listar Produtos (Exige Autenticacao REST)" << std::endl;
        std::cout << "2. Adicionar Produto (POST)" << std::endl;
        std::cout << "3. Deletar Produto (DELETE)" << std::endl;
        std::cout << "4. Realizar Venda (POST para /vendas)" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        std::cin.ignore(); // Limpa o buffer após o cin >> opcao

        switch(opcao) {
            case 1:
                // Passa o gestor validado no login para a API
                api.listarProdutos(gestorAtual);
                break;
                
            case 2: {
                std::string nome, desc;
                double preco;
                int qtd, id;

                std::cout << "ID: "; std::cin >> id;
                std::cin.ignore();
                std::cout << "Nome: "; std::getline(std::cin, nome);
                std::cout << "Descricao: "; std::getline(std::cin, desc);
                std::cout << "Preco: "; std::cin >> preco;
                std::cout << "Estoque: "; std::cin >> qtd;

                // Cria o produto
                auto novoProduto = std::make_shared<Produto>(id, nome, desc, preco, qtd);
                
                // Associa o vendedor logado ao novo produto (Agregação)
                novoProduto->setVendedor(gestorAtual);

                // Envia para o servidor
                api.adicionarProduto(novoProduto);
                break;
            }

            case 3: {
                int idParaDeletar;
                std::cout << "Digite o ID do produto para deletar: ";
                std::cin >> idParaDeletar;
                api.deletarProduto(idParaDeletar);
                break;
            }
            case 4: { // Opção de Venda
                int pid, qtd;
                std::cout << "ID do produto para venda: ";
                std::cin >> pid;
                std::cout << "Quantidade: ";
                std::cin >> qtd;
                
                // O gestor logado (gestorAtual) é passado automaticamente como o vendedor
                api.realizarVenda(pid, qtd, gestorAtual);
                break;
            }
                
            case 0:
                std::cout << "A encerrar sessao..." << std::endl;
                break;
                
            default:
                std::cout << "Opcao invalida!" << std::endl;
        }
<<<<<<< Updated upstream
    }
    catch (const std::exception& e) {
        exibirErro(std::string("Erro Inesperado: ") + e.what());
        return 1;
    }

=======
#include "protocols/Request.h"
#include "protocols/Reply.h"
#include "protocols/MessageType.h"
#include "network/TcpClient.h"
#include "utils/Config.h"

#include <iostream>
#include <vector>
#include <memory>

int main() {
    try {
        Config config("config/Config.txt");

        TcpClient client(config.getIp(), config.getPort());

        if (!client.connectToServer()) {
            std::cerr << "Falha ao conectar ao servidor.\n";
            return 1;
        }

        std::vector<std::shared_ptr<Produto>> lista = {
            // Produto Base: ID, Nome, Descrição, Preço, Estoque
            std::make_shared<Produto>(
                0, "Carregador", "USB-C Fast Charge", 79.90, 50),

            // Celular: Base + Marca, Modelo
            std::make_shared<Celular>(
                1, "Smartphone", "Android 14", 1999.90, 20,
                "Samsung", "Galaxy S23"),

            // Capa: Base + Modelo do Celular, Material (Ordem do Java!)
            std::make_shared<Capa>(
                2, "Capa Protetora", "Capa Anti-Impacto", 29.90, 30,
                "Galaxy S23", "Silicone"),

            // Pelicula: Base + Modelo do Celular, Tipo/Material (Ordem do Java!)
            std::make_shared<Pelicula>(
                3, "Película", "Proteção de Tela", 19.90, 40,
                "Galaxy S23", "Vidro Temperado"),

            // PowerBank: Base + Marca, Modelo, Capacidade (Ordem do Java!)
            std::make_shared<PowerBank>(
                4, "PowerBank", "Carregador Portátil", 149.90, 15,
                "Xiaomi", "PB-10000", 10000)
        };

        auto requestData = Request::buildAddProdutos(lista);

        // Envia a requisição
        if (!client.sendData(requestData)) {
            std::cerr << "Erro ao enviar a requisicao.\n";
            return 1;
        }

        // Recebe a resposta
        std::vector<char> replyData = client.receiveData();

        if (replyData.empty()) {
            std::cerr << "Erro ao receber resposta do servidor.\n";
            return 1;
        }

        // Interpreta a resposta
        Reply reply = Reply::parse(replyData);

        if (reply.getMessageType() ==
            static_cast<uint32_t>(MessageType::REPLY_SUCCESS)) {
            std::cout << "Servidor: " << reply.getMessage() << std::endl;
        } else {
            std::cerr << "Erro do servidor: "
                    << reply.getMessage() << std::endl;
        }

        client.closeConnection();
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

>>>>>>> Entrega_2_Invocacao_Remota
=======
    } while(opcao != 0);
    
>>>>>>> Stashed changes
    return 0;
}