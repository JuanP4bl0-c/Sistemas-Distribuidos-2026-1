#include "protocols/Request.h"
#include "modelos/Celular.h"
#include "modelos/Capa.h"
#include "modelos/Pelicula.h"
#include "modelos/PowerBank.h"
#include <sstream>
#include <iomanip>

// ➔ OPERAÇÃO 1: LISTAR (Gera o envelope JSON estruturado para o Despachante Java)
std::vector<char> Request::buildListProdutos() {
    std::stringstream ss;
    ss << "{"
       << "\"objectReference\":\"CatalogoRemoto\","
       << "\"methodId\":1,"
       << "\"arguments\":{}"
       << "}";
    
    std::string str = ss.str();
    return std::vector<char>(str.begin(), str.end());
}

// ➔ OPERAÇÃO 2: ADICIONAR (Gera os argumentos polimórficos lidos pelo Esqueleto Java)
std::vector<char> Request::buildAddProdutos(const std::vector<std::shared_ptr<Produto>>& produtos) {
    if (produtos.empty()) return std::vector<char>();

    // Pega o primeiro item da lista para corresponder ao arguments.getString("tipo") do Java
    auto p = produtos[0]; 
    std::stringstream ss;

    ss << "{"
       << "\"objectReference\":\"CatalogoRemoto\","
       << "\"methodId\":2,"
       << "\"arguments\":{";

    // Mapeia o enum de tipos para a string exata que o seu 'equalsIgnoreCase' do Java espera
    std::string tipoStr = "Produto";
    switch (p->getTipo()) {
        case TipoProduto::CELULAR:   tipoStr = "Celular"; break;
        case TipoProduto::CAPA:      tipoStr = "Capa"; break;
        case TipoProduto::PELICULA:  tipoStr = "Pelicula"; break;
        case TipoProduto::POWERBANK: tipoStr = "PowerBank"; break;
        default:                     tipoStr = "Produto"; break;
    }

    // Atributos comuns a todas as entidades
    ss << "\"tipo\":\"" << tipoStr << "\","
       << "\"id\":" << p->getId() << ","
       << "\"nome\":\"" << p->getNome() << "\","
       << "\"descricao\":\"" << p->getDescricao() << "\","
       << "\"preco\":" << std::fixed << std::setprecision(2) << p->getPreco() << ","
       << "\"quantidade\":" << p->getQuantidadeEstoque();

    // Injeta os campos específicos de cada subclasse através de dynamic_pointer_cast
    switch (p->getTipo()) {
        case TipoProduto::CELULAR: {
            auto celular = std::dynamic_pointer_cast<Celular>(p);
            if (celular) {
                ss << ",\"marca\":\"" << celular->getMarca() << "\",\"modelo\":\"" << celular->getModelo() << "\"";
            }
            break;
        }
        case TipoProduto::CAPA: {
            auto capa = std::dynamic_pointer_cast<Capa>(p);
            if (capa) {
                ss << ",\"modeloCelular\":\"" << capa->getModelo() << "\",\"material\":\"" << capa->getMaterial() << "\"";
            }
            break;
        }
        case TipoProduto::PELICULA: {
            auto pelicula = std::dynamic_pointer_cast<Pelicula>(p);
            if (pelicula) {
                ss << ",\"modeloCelular\":\"" << pelicula->getModelo() << "\",\"material\":\"" << pelicula->getMaterial() << "\"";
            }
            break;
        }
        case TipoProduto::POWERBANK: {
            auto powerbank = std::dynamic_pointer_cast<PowerBank>(p);
            if (powerbank) {
                ss << ",\"marca\":\"" << powerbank->getMarca() << "\",\"modelo\":\"" << powerbank->getModelo() << "\",\"capacidade\":" << powerbank->getCapacidade();
            }
            break;
        }
        default:
            break;
    }

    ss << "}}";

    std::string str = ss.str();
    return std::vector<char>(str.begin(), str.end());
}

// ➔ OPERAÇÃO 3: REMOVER
std::vector<char> Request::buildRemoveProduto(int id) {
    std::stringstream ss;
    ss << "{"
       << "\"objectReference\":\"CatalogoRemoto\","
       << "\"methodId\":3,"
       << "\"arguments\":{\"id\":" << id << "}"
       << "}";
    
    std::string str = ss.str();
    return std::vector<char>(str.begin(), str.end());
}