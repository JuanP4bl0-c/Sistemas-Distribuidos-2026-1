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
    } while(opcao != 0);
}