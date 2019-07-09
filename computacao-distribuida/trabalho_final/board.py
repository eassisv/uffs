class Board:
    water = '~'
    hit_water = 'o'
    crashed_boat = '#'

    def __init__(self, cols, lines):
        self.cols = cols
        self.lines = lines
        self.board = [[self.water] * cols for i in range(lines)]

    def __str__(self):
        s = ''
        for i in self.board:
            s += str(i) + '\n'
        return s

    def is_valid(self, size, x, y, horizon):
        if 0 <= x < (self.cols - size) and \
           0 <= y < (self.lines - size):
            if horizon:
                for i in range(x, size + x):
                    if self.board[y][i] != self.water:
                        return False
            else:
                for i in range(y, size + y):
                    if self.board[i][x] != self.water:
                        return False
            return True
        return False


    def insert(self, size, x, y, horizon):
        x, y = x - 1, y - 1
        if self.is_valid(size, x, y, horizon):
            if horizon:
                for i in range(x, size + x):
                    self.board[y][i] = str(size)
            else:
                for i in range(y, size + y):
                    self.board[i][x] = str(size)
            return True
        return False
