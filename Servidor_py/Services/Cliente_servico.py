import sys
import os
import grpc

# Adicionar raiz ao path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import produto_pb2
import produto_pb2_grpc
from Pojos.Cliente import Cliente

class ClienteServicer(produto_pb2_grpc.ClienteServiceServicer):
    """Serviço responsável por gerenciar clientes da loja"""
    
    def __init__(self):
        self.clientes = {}
        self._inicializar_dados()
    
    def _inicializar_dados(self):
        self.clientes[1] = Cliente(1, "João Silva", "joao@email.com", "11999999999", "Rua A, 123")
        self.clientes[2] = Cliente(2, "Maria Santos", "maria@email.com", "11888888888", "Rua B, 456")
    
    def RegistrarCliente(self, request, context):
        novo_id = max(self.clientes.keys()) + 1 if self.clientes else 1
        cliente = Cliente(novo_id, request.nome, request.email, request.telefone, request.endereco)
        self.clientes[novo_id] = cliente
        return produto_pb2.Cliente(
            id=cliente.id, nome=cliente.nome, email=cliente.email,
            telefone=cliente.telefone, endereco=cliente.endereco
        )
    
    def GetCliente(self, request, context):
        if request.id in self.clientes:
            c = self.clientes[request.id]
            return produto_pb2.Cliente(
                id=c.id, nome=c.nome, email=c.email,
                telefone=c.telefone, endereco=c.endereco
            )
        context.set_code(grpc.StatusCode.NOT_FOUND)
        context.set_details("Cliente não encontrado")
        return produto_pb2.Cliente()
    
    def ListarClientes(self, request, context):
        resposta = produto_pb2.ListaClientes()
        for c in self.clientes.values():
            resposta.clientes.add(
                id=c.id, nome=c.nome, email=c.email,
                telefone=c.telefone, endereco=c.endereco
            )
        return resposta