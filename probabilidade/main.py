# -*- coding: utf-8 -*-

fact = [1, 1]

def factorial(n):
    while len(fact) <= n:
        fact.append(len(fact) * fact[-1])
    return fact[n]

def binomio(n, x):
    return factorial(n) / (factorial(n - x) * factorial(x))

def individual(p, n, x):
    return binomio(n, x) * p ** x * (1.0 - p) ** (n - x)

def acumulativa(p, n, x):
    return sum([individual(p, n, i) for i in range(x + 1)])

print('Digite \"S\" para encerrar o programa')
while True:
    try:
        n = input('Digite o valor de n: ')
        if n == 'S': break
        x = input('Digite o valor de x: ')
        if x == 'S': break
        p = input('Digite o valor absoluto de p: ')
        if p == 'S': break
        n = int(n)
        x = int(x)
        p = list(map(lambda x: float(x.replace(',', '.')), p.split('/')))
        if len(p) == 2: p = p[0] / p[1]
        else: p = p[0]
        ans = individual(p, n, x)
        print('\nDistribuição binomial individual')
        print('p({}) = {:.4f} = {:.2f}%\n'.format(x, ans, ans * 100))
        ans = acumulativa(p, n, x)
        print('\nDistribuição binomial acumulativa')
        print('p({}) = {:.4f} = {:.2f}%\n'.format(x, ans, ans * 100))
    except ValueError:
        print('\nOs valores de n, x e p, devem ser valores numericos, ou digite S para sair\n')
        continue

