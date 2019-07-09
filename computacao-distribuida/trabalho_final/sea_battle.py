import os
import sys
import socket
from pickle import loads, dumps
from board import Board
from threading import Thread

vector = [0, 0]
lines = 5
cols = 5
myboard = Board(cols, lines)
enemyboard = Board(cols, lines)
myview = Board(cols, lines)
ship_size = 3
boat_size = 1
ships = 1
boats = 2
ports = [25010, 25011]
dht_addr = ("127.0.0.1", 25001)
running = True

def send_board():
    for i, line in zip(range(lines), enemyboard.board):
        data = dumps(line)
        sock = socket.socket()
        sock.connect(dht_addr)
        sock.send(dumps({"op": "insert", "hash": abs(hash(str(i))), "data": data}))
        data = loads(sock.recv(1024))
        if not data["inserted"]:
            print("Problems with DHT")
            sys.exit(0)

def load_view():
    print("Loading view...")
    for i in range(lines):
        sock = socket.socket()
        sock.connect(dht_addr)
        sock.send(dumps({"op": "search", "hash": abs(hash(str(i)))}))
        data = loads(sock.recv(1024))
        if not data["found"]:
            print("Problems with DHT")
            sys.exit(0)
        line = loads(data["data"])
        myview.update(line, i)
    erase()
    print(myview)

def erase():
    for i in range(lines):
        sock = socket.socket()
        sock.connect(dht_addr)
        sock.send(dumps({"op": "delete", "hash": abs(hash(str(i)))}))
        data = loads(sock.recv(1024))

def shot_coord():
    y = int(input('Line: '))
    x = int(input('Column: '))
    return (x, y)

def update_clock():
    vector[_id - 1] = max(vector) + 1

def calculate_vector(vec):
    global vector
    vector = list(max(x, y) for x, y in zip(vector, vec))

def verify_winner():
    for i in range(lines):
        for j in range(cols):
            if myboard.board[i][j] != '~' and \
                enemyboard.board[i][j] != '#':
                    return False
    return True

def loop():
    sock = socket.socket()
    sock.bind(("127.0.0.1", ports[_id - 1]))
    sock.settimeout(5)
    sock.listen(10)
    if _id == 2: print("Playing\n")
    while running:
        try:
            conn, _ = sock.accept()
        except socket.timeout:
            continue
        data = loads(conn.recv(1024))
        conn.shutdown(socket.SHUT_RDWR)
        conn.close()
        load_view()
        if data["winner"]:
            print("Winner!")
            sys.exit(0)
        calculate_vector(loads(data["vector"]))
        update_clock()
        if vector[_id - 1] % 2 != _id % 2:
            print(vector)
            print("Little Thief...")
            sys.exit(0)
        shot = loads(data["shot"])
        x, y = shot[0] - 1, shot[1] - 1
        if myboard.shot(x, y):
            enemyboard.board[y][x] = '#'
        else:
            enemyboard.board[y][x] = 'o'
        winner = verify_winner()
        send_board()
        data = dumps({"shot": dumps(shot_coord() if not winner else (0, 0)), "vector": dumps(vector), "winner": winner})
        sender = socket.socket()
        sender.connect(("127.0.0.1", ports[0 if _id == 2 else 1]))
        sender.send(data)
        if winner:
            print("Enemy Win...")
            sys.exit(0)

os.system('clear')
for i, size, printf in zip((ships, boats), \
    (ship_size, boat_size), ("Ships", "Boats")):
    for j in range(i):
        while True:
            try:
                print(printf, ' (size {})'.format(size))
                y = int(input('Line: ')) - 1
                x = int(input('Column: ')) - 1
                horizon = int(input('Horizontal? (No[0]): '))
                if myboard.insert(size, x, y, horizon):
                    break
                else:
                    print("Invalid value, try again")
            except ValueError:
                print('Write 3 numbers exactly')

os.system('clear')

_id = int(sys.argv[1])
mytime = False

if _id == 1:
    erase()
    send_board()
    print("Playing\n")
    sock = socket.socket()
    sock.connect(("127.0.0.1", ports[0 if _id == 2 else 1]))
    update_clock()
    print(myview)
    sock.send(dumps({"shot": dumps(shot_coord()), "vector": dumps(vector), "winner": False}))

rec = Thread(target=loop, name="Abacaxi")
rec.start()
try:
    rec.join()
except KeyboardInterrupt:
    running = False
    print("Exiting...")
