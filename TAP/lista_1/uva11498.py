while True:
    try:
        k = int(input())
        if k == 0: break
    except EOFError:
        break

    n, m = [int(x) for x in input().split(' ')]
    for i in range(k):
        x, y = [int(x) for x in input().split(' ')]
        if x == n or y == m:
            print('divisa')
        elif x > n:
            if y > m:
                print('NE')
            else:
                print('SE')
        else:
            if y > m:
                print('NO')
            else:
                print('SO')
