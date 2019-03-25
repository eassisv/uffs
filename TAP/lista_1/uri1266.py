while True:
    n = int(input())
    if n == 0: break
    ns = input().split(' ')
    try:
        i = ns.index('1')
    except ValueError:
        i = 0
    last = i
    ans = 0
    while True:
        if ns[i - 1] == '0' and ns[i] == '0':
            ns[i] = '1'
            ans = ans + 1
        i = (i + 1) % n
        if i == last: break

    print(ans)
