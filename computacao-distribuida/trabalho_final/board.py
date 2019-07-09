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
        if horizon:
            if 0 <= x and x + size <= self.cols and 0 <= y <= self.lines:
                for i in range(x, size + x):
                    if self.board[y][i] != self.water:
                        return False
                return True
        else:
            if 0 <= x <= self.cols and 0 <= y and y + size <= self.lines:
                for i in range(y, size + y):
                    if self.board[i][x] != self.water:
                        return False
                return True
        return False

    def update(self, line, idx):
        for i, l in zip(range(self.lines), line):
            self.board[idx][i] = l

    def shot(self, x, y):
        if 0 <= x < self.cols and 0 <= y < self.lines:
            if self.board[y][x] == self.water:
                return False
            return True
        return False

    def insert(self, size, x, y, horizon):
        if self.is_valid(size, x, y, horizon):
            if horizon:
                for i in range(x, size + x):
                    self.board[y][i] = str(size)
            else:
                for i in range(y, size + y):
                    self.board[i][x] = str(size)
            return True
        return False
