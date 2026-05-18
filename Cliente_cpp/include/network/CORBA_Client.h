#ifndef CORBA_CLIENT_H
#define CORBA_CLIENT_H

#include <vector>
#include <string>
#include "Servico.hh" // Stub gerado pelo IDL

class CorbaClient {
private:
    CORBA::ORB_var orb;
    CatalogoApp::ServicoCatalogo_var servidor; 
    bool inicializado;

public:
    // Construtor
    CorbaClient(int argc, char** argv, const std::string& nomeServico);
    
    // Destrutor
    ~CorbaClient();

    // Executa a chamada remota de 3 parâmetros condizente com o Java
    std::vector<char> doOperation(const std::string& objectRef, long methodId, const std::vector<char>& requestData);

    // Retorna o estado da conexão
    bool isConnected() const;
};

#endif // CORBA_CLIENT_H