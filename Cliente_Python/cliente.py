import requests
import json

URL  = "http://localhost:8000/api/produtos"

def listar_produtos():
    response = requests.get(URL)
    print("Produtos disponíveis:")
    print(response.json())

def adicionar_produto(nome, preco,estoque):
    novo_produto = {
        "tipo": "Produto",
        "nome": nome,
        "preco": preco,
        "estoque": estoque
    }
    # O 'json=' converte automaticamente para string JSON e define o header Content-Type
    response = requests.post(URL_BASE, json=novo_produto)
    print(f"Status: {response.status_code}")
    print(response.json())


if __name__ == "__main__":

    print("--- Cliente Python Ativo ---")
    
    while True:
        print("\n=== MENU CLIENTE PYTHON ===")
        print("1 - Listar produtos")
        print("2 - Adicionar produto")
        print("3 - Buscar produto por ID")
        print("4 - Remover produto por ID")
        print("0 - Sair")

        opcao = input("Escolha uma opção: ").strip()

        if opcao == "1":
            listar_produtos()
        elif opcao == "2":
            adicionar_produto()
        elif opcao == "3":
            buscar_produto_por_id()
        elif opcao == "4":
            remover_produto_por_id()
        elif opcao == "0":
            print("Saindo...")
            break
        else:
            print("Opção inválida.")