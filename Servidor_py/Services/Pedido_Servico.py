import sys
import os
import grpc

# Adicionar raiz ao path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import produto_pb2
import produto_pb2_grpc
from Pojos.Pedido import Pedido

class PedidoServicer(produto_pb2_grpc.PedidoServiceServicer):
    """Serviço responsável por gerenciar pedidos da loja"""
    
    def __init__(self, produto_serviceador, cliente_serviceador):
        self.pedidos = {}
        self.produto_serviceador = produto_serviceador
        self.cliente_serviceador = cliente_serviceador
        self._inicializar_dados()
    
    def _inicializar_dados(self):
        self.pedidos[1] = Pedido(1, 1, [1, 2], 3550.0, "Processando")
        self.pedidos[2] = Pedido(2, 2, [3], 15.0, "Entregue")
    
    def CriarPedido(self, request, context):
        novo_id = max(self.pedidos.keys()) + 1 if self.pedidos else 1
        pedido = Pedido(novo_id, request.cliente_id, list(request.produtos_ids), request.total, "Pendente")
        self.pedidos[novo_id] = pedido
        return produto_pb2.Pedido(
            id=pedido.id, cliente_id=pedido.cliente_id,
            produtos_ids=pedido.produtos_ids, total=pedido.total,
            status=pedido.status
        )
    
    def GetPedido(self, request, context):
        if request.id in self.pedidos:
            p = self.pedidos[request.id]
            return produto_pb2.Pedido(
                id=p.id, cliente_id=p.cliente_id,
                produtos_ids=p.produtos_ids, total=p.total,
                status=p.status
            )
        context.set_code(grpc.StatusCode.NOT_FOUND)
        context.set_details("Pedido não encontrado")
        return produto_pb2.Pedido()
    
    def ListarPedidos(self, request, context):
        resposta = produto_pb2.ListaPedidos()
        for ped in self.pedidos.values():
            if ped.cliente_id == request.id:
                resposta.pedidos.add(
                    id=ped.id, cliente_id=ped.cliente_id,
                    produtos_ids=ped.produtos_ids, total=ped.total,
                    status=ped.status
                )
        return resposta
    
    def AtualizarStatusPedido(self, request, context):
        if request.id in self.pedidos:
            self.pedidos[request.id].status = request.status
            p = self.pedidos[request.id]
            return produto_pb2.Pedido(
                id=p.id, cliente_id=p.cliente_id,
                produtos_ids=p.produtos_ids, total=p.total,
                status=p.status
            )
        context.set_code(grpc.StatusCode.NOT_FOUND)
        context.set_details("Pedido não encontrado")
        return produto_pb2.Pedido()