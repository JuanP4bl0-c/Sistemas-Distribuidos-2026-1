from modelos import Vendedor
from produto_api import ProdutoAPI


def realizar_login() -> Vendedor:
    print("\n=== LOGIN DE GESTOR ===")
    nome = input("Nome do Gestor: ").strip()
    vendid = input("ID do Gestor: ").strip()
    return Vendedor(nome=nome, id=vendid)


def executar_menu(api: ProdutoAPI, gestor_atual: Vendedor) -> None:
    while True:
        print("\n=== MENU PYTHON ===")
        print("1. Listar Produtos")
        print("2. Adicionar Produto")
        print("3. Deletar Produto")
        print("4. Realizar Venda")
        print("0. Sair")

        opcao = input("Escolha uma opcao: ").strip()

        if opcao == "1":
            api.listar_produtos(gestor_atual)
        elif opcao == "2":
            api.adicionar_produto(gestor_atual)
        elif opcao == "3":
            api.deletar_produto(gestor_atual)
        elif opcao == "4":
            api.realizar_venda(gestor_atual)
        elif opcao == "0":
            print("A encerrar sessao...")
            break
        else:
            print("Opcao invalida!")


def main() -> None:
    print("--- Cliente Python Ativo ---")

    try:
        api = ProdutoAPI()
    except Exception as erro:
        print(f"[Erro Critico] Falha ao carregar configuracao: {erro}")
        return

    gestor_atual = realizar_login()

    print("\n=====================================")
    print(" BEM-VINDO AO SISTEMA DE VENDAS")
    print(f" Gestor autenticado: {gestor_atual.nome} (ID: {gestor_atual.id})")
    print("=====================================")

    executar_menu(api, gestor_atual)