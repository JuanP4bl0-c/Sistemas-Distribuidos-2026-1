import grpc
from concurrent import futures
import produto_pb2
import produto_pb2_grpc
from modelo import Produto

class ProdutoServicer(produto_pb2_grpc.ProdutoServiceServicer):
    def __init__(self):
        self.produtos = {}
        self._inicializar_dados()
    
    def _inicializar_dados(self):
        self.produtos[1] = Produto(1, "Notebook", "Dell 15 polegadas", 3500.0, 10)
        self.produtos[2] = Produto(2, "Mouse", "Logitech sem fio", 50.0, 100)
    
    def GetProduto(self, request, context):
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
        resposta = produto_pb2.ListaProdutos()
        for p in self.produtos.values():
            resposta.produtos.add(
                id=p.id, nome=p.nome, descricao=p.descricao,
                preco=p.preco, estoque=p.estoque
            )
        return resposta

def servir():
    servidor = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    produto_pb2_grpc.add_ProdutoServiceServicer_to_server(ProdutoServicer(), servidor)
    servidor.add_insecure_port('[::]:50051')
    print("Servidor iniciado na porta 50051...")
    servidor.start()
    servidor.wait_for_termination()

if __name__ == '__main__':
    servir()