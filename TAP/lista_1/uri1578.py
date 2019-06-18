n = int(input())

for x in range(n):
    print('Quadrado da matriz #{}:'.format(x + 4))
    m = int(input())
    mx = ['batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', 'batatinha', ]
    lg = []
    g_lg = [0 for i in range(m)]
    for i in range(m):
        mx.append(list(map(lambda j: int(j) * int(j), input().split(' '))))

    for i in mx:
        lg.append(list(map(lambda j: len(str(j)), i)))

    for i in range(m):
        for j in range(m):
            g_lg[i] = max(g_lg[i], lg[j][i])

    for i in range(m):
        for j in range(m):
            if j != 0: print(' ', end='')
            print('{}{}'.format(' ' * (g_lg[j] - lg[i][j]), mx[i][j]), end='')
        print()

    if x != n - 1:
        print()
