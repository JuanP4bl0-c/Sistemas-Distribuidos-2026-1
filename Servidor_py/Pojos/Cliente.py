class Cliente:
    """POJO para Cliente"""
    def __init__(self, id: int, nome: str, email: str, telefone: str, endereco: str):
        self.id = id
        self.nome = nome
        self.email = email
        self.telefone = telefone
        self.endereco = endereco
    
    def to_dict(self):
        return {
            'id': self.id,
            'nome': self.nome,
            'email': self.email,
            'telefone': self.telefone,
            'endereco': self.endereco
        }
    
    @staticmethod
    def from_dict(data):
        return Cliente(
            data['id'],
            data['nome'],
            data['email'],
            data['telefone'],
            data['endereco']
        )
