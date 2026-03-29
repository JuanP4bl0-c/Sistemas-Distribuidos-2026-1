import sys
import os
import grpc

# Adicionar raiz ao path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import produto_pb2
import produto_pb2_grpc
from Pojos.produto import Produto

# ==================== SERVIÇO DE PRODUTOS ====================
class ProdutoServicer(produto_pb2_grpc.ProdutoServiceServicer):
    """Serviço responsável por gerenciar produtos da loja"""
    
    def __init__(self):
        self.produtos = {}
        self._inicializar_dados()
    
    def _inicializar_dados(self):
        """Inicializa dados de exemplo no servidor"""
        self.produtos[1] = Produto(1, "Notebook", "Positivo", 3500.0, 10)
        self.produtos[2] = Produto(2, "Mouse", "Logitech sem fio", 50.0, 100)
        self.produtos[3] = Produto(3, "Pelicula", "Xiaomi", 15, 10)
    
    def GetProduto(self, request, context):
        """Busca um produto pelo ID"""
        if request.id in self.produtos:
            p = self.produtos[request.id]
            return produto_pb2.Produto(
                id=p.id, nome=p.nome, descricao=p.descricao,
                preco=p.preco, estoque=p.estoque
            )
        context.set_code(grpc.StatusCode.NOT_FOUND)
        context.set_details("Produto não encontrado")
        return produto_pb2.Produto()
    
    def ListarProdutos(self, request, context):
        """Lista todos os produtos disponíveis"""
        resposta = produto_pb2.ListaProdutos()
        for p in self.produtos.values():
            resposta.produtos.add(
                id=p.id, nome=p.nome, descricao=p.descricao,
                preco=p.preco, estoque=p.estoque
            )
        return resposta
    
    def AtualizarEstoque(self, request, context):
        """Atualiza o estoque de um produto"""
        if request.id in self.produtos:
            self.produtos[request.id].estoque = request.quantidade
            p = self.produtos[request.id]
            return produto_pb2.Produto(
                id=p.id, nome=p.nome, descricao=p.descricao,
                preco=p.preco, estoque=p.estoque
            )
        context.set_code(grpc.StatusCode.NOT_FOUND)
        context.set_details("Produto não encontrado")
        return produto_pb2.Produto()
