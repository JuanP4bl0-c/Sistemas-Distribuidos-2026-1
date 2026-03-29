import sys
import os
import grpc
from concurrent import futures

# Adicionar raiz ao path para importações relativas
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import produto_pb2
import produto_pb2_grpc
from Pojos.produto import Produto
from Pojos.Cliente import Cliente
from Pojos.Pedido import Pedido
from Services.Cliente_servico import ClienteServicer
from Services.Pedido_Servico import PedidoServicer
from Services.Produto_Servico import ProdutoServicer


# ==================== FUNÇÃO PRINCIPAL ====================
def servir():
    """Inicia o servidor gRPC com todos os serviços"""
    servidor = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    # Criar instâncias dos serviços
    produto_serviceador = ProdutoServicer()
    cliente_serviceador = ClienteServicer()
    pedido_serviceador = PedidoServicer(produto_serviceador, cliente_serviceador)
    
    # Registrar todos os serviços no servidor
    produto_pb2_grpc.add_ProdutoServiceServicer_to_server(produto_serviceador, servidor)
    produto_pb2_grpc.add_ClienteServiceServicer_to_server(cliente_serviceador, servidor)
    produto_pb2_grpc.add_PedidoServiceServicer_to_server(pedido_serviceador, servidor)
    
    # Configurar porta e iniciar
    servidor.add_insecure_port('[::]:50051')
    print("=" * 60)
    print("Servidor gRPC iniciado na porta 50051")
    print("=" * 60)
    print("Serviços disponíveis:")
    print("  ✓ ProdutoService - Gerenciamento de produtos")
    print("  ✓ ClienteService - Gerenciamento de clientes")
    print("  ✓ PedidoService - Gerenciamento de pedidos")
    print("=" * 60)
    servidor.start()
    servidor.wait_for_termination()

if __name__ == '__main__':
    servir()