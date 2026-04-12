import sys
import os
import socket
import json
import threading

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

#Modelos
from Pojo.Produto_Model import Produto

#Arquivos confidenciais IP e PORTA
from important import Host, Porta  

#dados em memória inicial
Produtos_Dados = {
    1: Produto(1, "Notebook", "Dell 15 polegadas", 3500.0, 10),
    2: Produto(2, "Mouse", "Logitech sem fio", 50.0, 100),
    3: Produto(3, "Pelicula", "Xiaomi", 15.0, 50)
}


def processar_requisicao(dados):
    try:
        comando = dados.strip()
        
        #listar produtos
        if comando == "LISTAR_PRODUTOS":
            resultado = [p.to_dict() for p in Produtos_Dados.values()]
            return json.dumps({"status": "sucesso", "dados": resultado})
        
        #buscar produto específico
        elif comando.startswith("GET_PRODUTO:"):
            id_produto = int(comando.split(":")[1])
            if id_produto in Produtos_Dados:
                return json.dumps({"status": "sucesso", "dados": Produtos_Dados[id_produto].to_dict()})
            return json.dumps({"status": "erro", "mensagem": "Produto não encontrado"})
        
        #criar produto
        elif comando.startswith("CRIAR_PRODUTO:"):
            partes = comando.split(":")
            novo_id = max(Produtos_Dados.keys()) + 1 if Produtos_Dados else 1
            novo_produto = Produto(novo_id, partes[1], partes[2], float(partes[3]), int(partes[4]))
            Produtos_Dados[novo_id] = novo_produto
            return json.dumps({"status": "sucesso", "dados": novo_produto.to_dict()})
        
        #atualizar estoque
        elif comando.startswith("ATUALIZAR_ESTOQUE:"):
            partes = comando.split(":")
            id_produto = int(partes[1])
            if id_produto in Produtos_Dados:
                Produtos_Dados[id_produto].estoque = int(partes[2])
                return json.dumps({"status": "sucesso", "dados": Produtos_Dados[id_produto].to_dict()})
            return json.dumps({"status": "erro", "mensagem": "Produto não encontrado"})
        
        else:
            return json.dumps({"status": "erro", "mensagem": "Comando desconhecido"})
    except Exception as e:
        return json.dumps({"status": "erro", "mensagem": f"Erro ao processar requisição: {str(e)}"})

def gerenciar_conexao(conexao, endereco):
    print("Cliente conectado")
    try:
        while True:
            dados = conexao.recv(1024).decode('utf-8')
            if not dados:
                break
            print(f"→ Requisição de {endereco}: {dados[:50]}...")
            resposta = processar_requisicao(dados)
            conexao.send(resposta.encode('utf-8'))
    
    except Exception as e:
        print(f"✗ Erro na conexão {endereco}: {str(e)}")
    finally:
        conexao.close()

def iniciar_servidor():
    servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
        servidor.bind((Host,Porta))
        servidor.listen(5)
        print("Servidor TCP rodando...")
        
        while (True):
            
            conexao, endereco = servidor.accept()
            print(f"Conexão recebida de {endereco}")
            thread = threading.Thread(target=gerenciar_conexao, args=(conexao, endereco))
            thread.daemon = True
            thread.start()
        
    except KeyboardInterrupt:
        print("Servidor encerrado.")
    finally:
        servidor.close()
        print("Servidor finalizado.")

if __name__ == "__main__":
    iniciar_servidor()
