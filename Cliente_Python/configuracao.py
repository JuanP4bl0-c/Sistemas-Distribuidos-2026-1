from pathlib import Path


CONFIG_PATH = Path(__file__).resolve().parent / "config" / "Config.txt"


class Config:
    def __init__(self, caminho: Path = CONFIG_PATH):
        self.ip = "127.0.0.1"
        self.port = 8000

        if not caminho.exists():
            raise FileNotFoundError(f"Nao foi possivel abrir o arquivo de configuracao: {caminho}")

        with caminho.open("r", encoding="utf-8") as arquivo:
            for linha in arquivo:
                linha = linha.strip()
                if not linha or "=" not in linha:
                    continue

                chave, valor = linha.split("=", 1)
                chave = chave.strip().upper()
                valor = valor.strip()

                if chave == "IP":
                    self.ip = valor
                elif chave == "PORT":
                    self.port = int(valor)

        if not self.ip or not self.port:
            raise ValueError("Configuracao invalida no arquivo.")