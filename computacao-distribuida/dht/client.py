import socket, os
from pickle import loads, dumps

# export PYTHONHASHSEED=0


if __name__ == "__main__":
    servers_port = [25001, 25002, 25003, 25004]
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
        _hash = abs(hash(data))
        msg = {"op": op, "hash": _hash, "data": data}
        port = servers_port[_hash % 4]
        sock = socket.socket()
        sock.connect(("127.0.0.1", port))
        sock.send(dumps(msg))
        data = loads(sock.recv(1024))
        if op == 1:
            if data["found"]:
                print("Dado encontrado no servidor {}".format(data["id"]))
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
