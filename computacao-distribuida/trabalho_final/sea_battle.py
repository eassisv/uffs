import sys
from board import Board

turn = 0
lines = 10
cols = 15
board = Board(cols, lines)
ship_size = 5
boat_size = 2
ships = 2
boats = 3

for i, size, printf in zip((ships, boats), \
    (ship_size, boat_size), ("Ships", "Boats")):
    print(printf)
    for j in range(i):
        while True:
            print("x y horizontal?")
            try:
                x, y, horizon = map(int, input().split())
                if not board.insert(size, x, y, horizon):
                    print("Invalid position, try again")
                else:
                    break
            except ValueError:
                print('Write 3 numbers exactly')

print(board)
