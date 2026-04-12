class Produto:
    """POJO para Produto"""
    def __init__(self, id: int, nome: str, descricao: str, preco: float, estoque: int):
        self.id = id
        self.nome = nome
        self.descricao = descricao
        self.preco = preco
        self.estoque = estoque
    
    def to_dict(self):
        return {
            'id': self.id,
            'nome': self.nome,
            'descricao': self.descricao,
            'preco': self.preco,
            'estoque': self.estoque
        }
    
    @staticmethod
    def from_dict(data):
        return Produto(
            data['id'],
            data['nome'],
            data['descricao'],
            data['preco'],
            data['estoque']
        )