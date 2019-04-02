# -*- coding: utf-8 -*-

import math

def binomio(n, x):
    return math.factorial(n) / (math.factorial(n - x) * math.factorial(x))


print('Digite \"S\" para encerrar o programa')
while True:
    try:
        n = input('n: ')
        if n == 'S': break
        x = input('x: ')
        if x == 'S': break
        p = input('p: ')
        if p == 'S': break
        n = int(n)
        x = int(x)
        p = float(p.replace(',', '.'))
    except ValueError:
        print('Os valores de n, x e p, devem ser valores numericos, ou digite S para sair')
        continue

    print(p)
    ans = binomio(n, x) * p**x * (1.0 - p)**(n - x)
    print('p(x) = {:.4f} = {:.2f}%'.format(ans, ans * 100))


