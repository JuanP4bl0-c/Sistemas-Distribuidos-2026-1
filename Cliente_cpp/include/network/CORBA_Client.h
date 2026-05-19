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
    /// Construtor: inicializa o ORB e resolve o objeto remoto pelo NameService
    CorbaClient(int argc, char** argv, const std::string& nomeServico);

    /// Destrutor: limpa recursos do ORB
    ~CorbaClient();

    /// Executa uma operação remota enviando `requestData` e retornando os bytes da resposta
    std::vector<char> doOperation(const std::string& objectRef, long methodId, const std::vector<char>& requestData);

    /// Indica se o cliente está conectado ao serviço remoto
    bool isConnected() const;
};

#endif // CORBA_CLIENT_H