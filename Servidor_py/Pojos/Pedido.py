class Pedido:
    """POJO para Pedido"""
    def __init__(self, id: int, cliente_id: int, produtos_ids: list, total: float, status: str):
        self.id = id
        self.cliente_id = cliente_id
        self.produtos_ids = produtos_ids
        self.total = total
        self.status = status
    
    def to_dict(self):
        return {
            'id': self.id,
            'cliente_id': self.cliente_id,
            'produtos_ids': self.produtos_ids,
            'total': self.total,
            'status': self.status
        }
    
    @staticmethod
    def from_dict(data):
        return Pedido(
            data['id'],
            data['cliente_id'],
            data['produtos_ids'],
            data['total'],
            data['status']
        )