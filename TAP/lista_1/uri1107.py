while True:
    a, c = list(int(x) for x in input().split(' '))
    if a == 0 and c == 0:
        break
    vs = list(int(x) for x in input().split(' '))
    ans = 0
    p = a
    for i in vs:
        if i < p:
            ans = ans + p - i
        p = i

    print(ans)
