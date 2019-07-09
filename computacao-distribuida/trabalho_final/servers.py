import socket, sys
from threading import Thread
from pickle import loads, dumps

running = False
ports = [25001, 25002, 25003, 25004]
addr = "127.0.0.1"


def insertion(data, hash_table):
    _hash = abs(hash(data["hash"]))
    key = _hash % len(hash_table)
    done = False
    for i in range(0, len(hash_table) - 1):
        if hash_table[(key + i) % len(hash_table)] == None:
            hash_table[(key + i) % len(hash_table)] = (_hash, data)
            done = True
            break
    if done:
        ans = {"inserted": True, "hash": data["hash"]}
    else:
        ans = {"inserted": False}
    return ans


def search(data, hash_table):
    _hash = abs(hash(data["hash"]))
    key = _hash % len(hash_table)
    found = False
    for i in range(0, len(hash_table) - 1):
        if hash_table[(key + i) % len(hash_table)] == None:
            continue
        if (
            hash_table[(key + i) % len(hash_table)][1]["hash"] == data["hash"]
            and hash_table[(key + i) % len(hash_table)][0] == _hash
        ):
            ans = {"found": True, "data": hash_table[(key + i) % len(hash_table)][1]["data"]}
            found = True
            break
    if not found:
        ans = {"found": False}
    return ans


def remove(data, hash_table):
    _hash = abs(hash(data["hash"]))
    key = _hash % len(hash_table)
    removed = False
    for i in range(0, len(hash_table) - 1):
        if hash_table[(key + i) % len(hash_table)] == None:
            continue
        if (
            hash_table[(key + i) % len(hash_table)][1]["hash"] == data["hash"]
            and hash_table[(key + i) % len(hash_table)][0] == _hash
        ):
            hash_table[key + i] = None
            removed = True
            break
    if removed:
        ans = {"removed": True}
    else:
        ans = {"removed": False}
    return ans


def server(_id, port):
    hash_table = [None] * 8
    hashs = set([_id * 8 + i for i in range(8)])
    sock = socket.socket()
    sock.bind(("127.0.0.1", port))
    sock.settimeout(5)
    sock.listen(10)
    while running:
        try:
            conn, _ = sock.accept()
        except socket.timeout:
            continue
        data = loads(conn.recv(1024))
        print("server id {} receive {} mod 32 = {}".format(_id, data, data["hash"] % 32))
        if (data["hash"] % 32) not in hashs:
            sender = socket.socket()
            sender.connect((addr, ports[_id + 1]))
            sender.send(dumps(data))
        else:
            print("É meu")

        if data["op"] == 'search':
            ans = search(data, hash_table)
        elif data["op"] == 'insert':
            ans = insertion(data, hash_table)
        else:
            ans = remove(data, hash_table)
        ans["id"] = _id
        conn.send(dumps(ans))
        conn.shutdown(socket.SHUT_RDWR)
        conn.close()


if __name__ == "__main__":
    servers = []
    running = True
    for _id, port in zip(range(0, 4), ports):
        servers.append(Thread(target=server, name=f"server_{port}", args=(_id, port)))
        servers[-1].start()
    try:
        for s in servers:
            s.join()
    except KeyboardInterrupt:
        print("\r\rSaindo...")
        running = False
