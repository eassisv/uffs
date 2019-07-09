import socket, os
from pickle import loads, dumps

PYTHONHASHSEED = 0

if __name__ == "__main__":
    while True:
        print("1 - buscar dado\n2 - inserir dado\n3 - remover dado\n0 - sair")
        try:
            op = int(input("-> "))
            if op < 0 or op > 3:
                raise ValueError
        except ValueError:
            print("Opção inválida")
            continue
        if op == 0:
            print("Saindo...")
            break
        print("Digite o dado: ", end="")
        data = input()
        data = [1, 2, 3, 4]
        data = dumps(data)
        _hash = abs(hash(data))
        ops = ["search", "insert", "delete"]
        msg = {"op": ops[op - 1], "hash": _hash, "data": data}
        port = 25001
        sock = socket.socket()
        sock.connect(("127.0.0.1", port))
        sock.send(dumps(msg))
        data = loads(sock.recv(1024))
        print(data)
        if op == 1:
            if data["found"]:
                print("Dado encontrado no servidor {}".format(data["id"]))
                print(loads(data["data"]))
            else:
                print("Dado não encontrado")
        elif op == 2:
            if data["inserted"]:
                print("Dado inserido no servidor {}".format(data["id"]))
            else:
                print("O dado não foi inserido")
        elif op == 3:
            if data["removed"]:
                print("Dado removido do servidor {}".format(data["id"]))
            else:
                print("Dado não encontrado para remoção")
