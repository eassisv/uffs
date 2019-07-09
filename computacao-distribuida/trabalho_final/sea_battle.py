import sys
import socket
from pickle import loads, dumps
from board import Board
from threading import Thread

vector = [0, 0]
lines = 10
cols = 15
myboard = Board(cols, lines)
enemyboard = Board(cols, lines)
myview = Board(cols, lines)
ship_size = 5
boat_size = 2
ships = 1
boats = 1
ports = [25010, 25011]
dht_addr = ("127.0.0.1", 25001)
running = True

for i, size, printf in zip((ships, boats), \
    (ship_size, boat_size), ("Ships", "Boats")):
    print(printf)
    for j in range(i):
        try:
            while True:
                print("x y horizontal?")
                x, y, horizon = map(int, input().split())
                if myboard.insert(size, x, y, horizon):
                    break
                else:
                    print("Invalid value, try again")
        except ValueError:
            print('Write 3 numbers exactly')

_id = int(sys.argv[1])
mytime = False

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
    print("Loaing view...")
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
        if not data["removed"]:
            print("Problems with DHT")
            sys.exit(0)

def shot_coord():
    x = int(input('x: '))
    y = int(input('y: '))
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
    while running:
        try:
            conn, _ = sock.accept()
        except socket.timeout:
            continue
        data = loads(conn.recv(1024))
        conn.shutdown(socket.SHUT_RDWR)
        conn.close()
        if data["winner"]:
            print("Winner!")
            sys.exit(0)
        calculate_vector(loads(data["vector"]))
        update_clock()
        if vector[_id - 1] % 2 != _id % 2:
            print(vector)
            print("Little Thief...")
            sys.exit(0)
        load_view()
        shot = loads(data["shot"])
        enemyboard.shot(shot[0], shot[1])
        winner = verify_winner()
        send_board()
        data = dumps({"shot": dumps(shot_coord()), "vector": dumps(vector), "winner": winner})
        sender = socket.socket()
        sender.connect(("127.0.0.1", ports[0 if _id == 2 else 1]))
        sock.send(data)
        if winner:
            print("Enemy Win...")
            sys.exit(0)

if _id == 1:
    send_board()
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
