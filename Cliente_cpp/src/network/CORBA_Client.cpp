#include "network/CORBA_Client.h"
#include <iostream>
#include <stdexcept>

// Implementação do Construtor
CorbaClient::CorbaClient(int argc, char** argv, const std::string& nomeServico) 
    : inicializado(false) {
    try {
        // 1. Inicializa o ORB interno do omniORB
        orb = CORBA::ORB_init(argc, argv);

        // 2. Resolve o Serviço de Nomes inicial
        CORBA::Object_var objNS = orb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var inc = CosNaming::NamingContext::_narrow(objNS);

        if (CORBA::is_nil(inc)) {
            std::cerr << "[CORBA] Erro: Não foi possível resolver o NameService.\n";
            return;
        }

        // 3. Prepara o nome estruturado do serviço
        CosNaming::Name name;
        name.length(1);
        name[0].id = CORBA::string_dup(nomeServico.c_str());

        // 4. Resolve o objeto do servidor Java e faz o unchecked_narrow
        CORBA::Object_var objServidor = inc->resolve(name);
        servidor = CatalogoApp::ServicoCatalogo::_unchecked_narrow(objServidor);

        if (CORBA::is_nil(servidor)) {
            std::cerr << "[CORBA] Erro: Objeto do servidor é nulo após o unchecked_narrow.\n";
            return;
        }

        inicializado = true;
        std::cout << "[CORBA] Cliente conectado com sucesso ao serviço: " << nomeServico << "\n";

    } catch (const CORBA::Exception& e) {
        std::cerr << "[CORBA] Exceção na inicialização: " << e._name() << "\n";
    }
}

// Implementação do Destrutor
CorbaClient::~CorbaClient() {
    try {
        if (!CORBA::is_nil(orb)) {
            orb->destroy();
        }
    } catch (...) {
        // Destrutores não devem lançar exceções em C++
    }
}

// Implementação do método de checagem
bool CorbaClient::isConnected() const {
    return inicializado;
}

// Implementação do método principal de transmissão
std::vector<char> CorbaClient::doOperation(const std::string& objectRef, long methodId, const std::vector<char>& requestData) {
    if (!inicializado) {
        throw std::runtime_error("Tentativa de chamar operação em um cliente CORBA não inicializado.");
    }

    try {
        // 1. Aloca e copia os elementos do std::vector nativo para o ByteArray do CORBA
        CatalogoApp::ByteArray argsCORBA;
        argsCORBA.length(requestData.size());
        for (size_t i = 0; i < requestData.size(); ++i) {
            argsCORBA[i] = requestData[i];
        }

        // 2. Dispara a chamada remota através do Stub transmitindo os 3 parâmetros
        CatalogoApp::ByteArray* respostaCORBA = servidor->doOperation(
            objectRef.c_str(),
            static_cast<CORBA::Long>(methodId),
            argsCORBA
        );

        // 3. Transcreve o resultado binário de volta para o std::vector do C++
        std::vector<char> replyData(
            respostaCORBA->get_buffer(),
            respostaCORBA->get_buffer() + respostaCORBA->length()
        );

        // 4. Desaloca o ponteiro de memória criado pelo Stub
        delete respostaCORBA;

        return replyData;

    } catch (const CORBA::Exception& e) {
        std::cerr << "[CORBA] Falha durante a execução remota: " << e._name() << "\n";
        return std::vector<char>(); 
    }
}