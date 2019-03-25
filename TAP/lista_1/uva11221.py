from math import sqrt

n = int(input())
for c in range(n):
    print('Case #{}:'.format(c + 1))
    l = ''
    for i in input():
        if i.isalpha():
            l = l + i

    inv_l = l[::-1]
    x = int(sqrt(len(l)))
    if x * x == len(l) and l[:len(l)//2] == inv_l[:len(l)//2]: print(x)
    else: print('No magic :(')
