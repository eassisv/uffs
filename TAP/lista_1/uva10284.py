while True:
    board = [[] for i in range(8)]
    try:
        l = 0
        for i in input().split('/'):
            for j in i:
                if j.isdecimal():
                    board[l].extend('.' * int(j))
                else:
                    board[l].append(j)
            l = l + 1

        def check(i, j):
            if 0 <= i < 8 and 0 <= j < 8:
                return True if board[i][j] == '.' or board[i][j] == '*' else False
            return False

        def rook(i, j):
            for x in range(1, 8):
                if check(i + x, j): board[i + x][j] = '*'
                else: break
            for x in range(1, 8):
                if check(i - x, j): board[i - x][j] = '*'
                else: break
            for x in range(1, 8):
                if check(i, j + x): board[i][j + x] = '*'
                else: break
            for x in range(1, 8):
                if check(i, j - x): board[i][j - x] = '*'
                else: break

        def bishop(i, j):
            for x in range(1, 8):
                if check(i + x,j + x): board[i + x][j + x] = '*'
                else: break
            for x in range(1, 8):
                if check(i + x, j - x): board[i + x][j - x] = '*'
                else: break
            for x in range(1, 8):
                if check(i - x, j - x): board[i - x][j - x] = '*'
                else: break
            for x in range(1, 8):
                if check(i - x, j + x): board[i - x][j + x] = '*'
                else: break

        def queen(i, j):
            rook(i, j)
            bishop(i, j)

        def king(i, j):
            if check(i + 1, j): board[i + 1][j] = '*'
            if check(i - 1, j): board[i - 1][j] = '*'
            if check(i, j + 1): board[i][j + 1] = '*'
            if check(i, j - 1): board[i][j - 1] = '*'
            if check(i + 1, j + 1): board[i + 1][j + 1] = '*'
            if check(i + 1, j - 1): board[i + 1][j - 1] = '*'
            if check(i - 1, j + 1): board[i - 1][j + 1] = '*'
            if check(i - 1, j - 1): board[i - 1][j - 1] = '*'

        def knight(i, j):
            if check(i + 2, j + 1): board[i + 2][j + 1] = '*'
            if check(i + 2, j - 1): board[i + 2][j - 1] = '*'
            if check(i - 2, j + 1): board[i - 2][j + 1] = '*'
            if check(i - 2, j - 1): board[i - 2][j - 1] = '*'
            if check(i + 1, j + 2): board[i + 1][j + 2] = '*'
            if check(i - 1, j + 2): board[i - 1][j + 2] = '*'
            if check(i + 1, j - 2): board[i + 1][j - 2] = '*'
            if check(i - 1, j - 2): board[i - 1][j - 2] = '*'

        def w_pawn(i, j):
            if check(i - 1, j - 1): board[i - 1][j - 1] = '*'
            if check(i - 1, j + 1): board[i - 1][j + 1] = '*'

        def b_pawn(i, j):
            if check(i + 1, j - 1): board[i + 1][j - 1] = '*'
            if check(i + 1, j + 1): board[i + 1][j + 1] = '*'

        opt = {
                'q': queen,
                'Q': queen,
                'k': king,
                'K': king,
                'p': b_pawn,
                'P': w_pawn,
                'n': knight,
                'N': knight,
                'r': rook,
                'R': rook,
                'b': bishop,
                'B': bishop
              }

        if len(board[0]) == 0: break

        for i in range(len(board)):
            for j in range(len(board)):
                if board[i][j] != '.' and board[i][j] != '*':
                    opt[board[i][j]](i, j)
        ans = 0
        for i in board:
            for j in i:
                if j == '.': ans = ans + 1

        print(ans)

    except EOFError:
        break
