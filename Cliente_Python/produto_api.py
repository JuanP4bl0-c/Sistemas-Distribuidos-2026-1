import json
from urllib import error, request

from configuracao import Config
from modelos import Vendedor


class ProdutoAPI:
    def __init__(self):
        configuracao = Config()
        self.base_url = f"http://{configuracao.ip}:{configuracao.port}"
        print(f"[Sistema] API inicializada. Apontando para: {self.base_url}")

    @staticmethod
    def _headers_gestor(gestor: Vendedor) -> dict[str, str]:
        return {
            "X-Gestor-ID": gestor.id,
            "X-Gestor-Nome": gestor.nome,
            "Content-Type": "application/json; charset=UTF-8",
        }

    @staticmethod
    def _imprimir_resposta(status: int, corpo: str) -> None:
        print(f"Status: {status}")
        try:
            print(json.loads(corpo))
        except ValueError:
            print(corpo)

    def _enviar_requisicao(
        self,
        metodo: str,
        caminho: str,
        payload: dict | None = None,
        headers: dict[str, str] | None = None,
    ) -> tuple[int, str]:
        url = f"{self.base_url}{caminho}"
        corpo = None
        request_headers = headers.copy() if headers else {}

        if payload is not None:
            corpo = json.dumps(payload, ensure_ascii=False).encode("utf-8")
            request_headers.setdefault("Content-Type", "application/json; charset=UTF-8")

        requisicao = request.Request(url=url, data=corpo, headers=request_headers, method=metodo)

        try:
            with request.urlopen(requisicao, timeout=10) as resposta:
                return resposta.status, resposta.read().decode("utf-8")
        except error.HTTPError as erro_http:
            return erro_http.code, erro_http.read().decode("utf-8")

    def listar_produtos(self, gestor: Vendedor) -> None:
        print(f"\n[API] {gestor.nome} esta solicitando o catalogo de vendas...")
        try:
            status, corpo = self._enviar_requisicao("GET", "/api/produtos", headers=self._headers_gestor(gestor))
            print("--- Itens do Catalogo de Vendas ---")
            self._imprimir_resposta(status, corpo)
        except error.URLError as erro:
            print(f"[API] Erro de conexao (GET): {erro}")

    def adicionar_produto(self, gestor: Vendedor) -> None:
        print("\n[API] Enviando produto para o servidor...")

        try:
            id_produto = int(input("ID: ").strip())
            nome = input("Nome: ").strip()
            descricao = input("Descricao: ").strip()
            preco = float(input("Preco: ").strip())
            estoque = int(input("Estoque: ").strip())
        except ValueError:
            print("[API] Valores invalidos para o produto.")
            return

        payload = {
            "tipo": "Produto",
            "id": id_produto,
            "nome": nome,
            "descricao": descricao,
            "preco": preco,
            "estoque": estoque,
        }

        try:
            status, corpo = self._enviar_requisicao("POST", "/api/produtos", payload=payload, headers=self._headers_gestor(gestor))
            print("[API] Produto enviado com sucesso!")
            self._imprimir_resposta(status, corpo)
        except error.URLError as erro:
            print(f"[API] Erro ao adicionar produto (POST): {erro}")

    def deletar_produto(self, gestor: Vendedor) -> None:
        try:
            id_produto = int(input("Digite o ID do produto para deletar: ").strip())
        except ValueError:
            print("[API] ID invalido.")
            return

        print(f"\n[API] Solicitando exclusao do Produto ID: {id_produto}...")
        try:
            status, corpo = self._enviar_requisicao("DELETE", f"/api/produtos/{id_produto}", headers=self._headers_gestor(gestor))
            print("--- Resposta do Servidor ---")
            self._imprimir_resposta(status, corpo)
        except error.URLError as erro:
            print(f"[API] Erro na exclusao (DELETE): {erro}")

    def realizar_venda(self, gestor: Vendedor) -> None:
        try:
            produto_id = int(input("ID do produto para venda: ").strip())
            quantidade = int(input("Quantidade: ").strip())
        except ValueError:
            print("[API] Valores invalidos para a venda.")
            return

        payload = {
            "produto_id": produto_id,
            "quantidade": quantidade,
            "vendedor_id": gestor.id,
            "vendedor_nome": gestor.nome,
        }

        print(f"\n[API] Enviando pedido de venda: {payload}")
        try:
            status, corpo = self._enviar_requisicao("POST", "/api/vendas", payload=payload, headers=self._headers_gestor(gestor))
            self._imprimir_resposta(status, corpo)
        except error.URLError as erro:
            print(f"[API] Falha ao conectar no servidor de vendas: {erro}")