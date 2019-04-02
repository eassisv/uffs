fact = [1, 1]

def factorial(n):
    while len(fact) <= n:
        fact.append(len(fact) * fact[-1])
    return fact[n]

def binomio(n, x):
    return factorial(n) / (factorial(n - x) * factorial(x))

def acumulativa(p, n, x):
    ans = float(0)
    for i in range(x):
        ans += binomio(n, i) * p**i * (1.0 - p)**(n - i)
    return ans


if __name__ == '__main__':
    print('Digite "S" para sair')
    print('Será calculado o valor acumulado entre x1 e x2')
    while True:
        try:
            n = input('n: ')
            if n == 'S': break
            x1 = input('x1: ')
            if x1 == 'S': break
            x2 = input('x2: ')
            if x2 == 'S': break
            p = input('p: ')
            if p == 'S': break

            n = int(n)
            x1 = int(x1)
            x2 = int(x2)
            p = float(p.replace(',', '.'))
        except ValueError:
            print('Os valores de n, x1, x2 e p, devem ser numericos, ou digite "S" para sair')
            continue

        ans = acumulativa(p, n, max(x1, x2)) - acumulativa(p, n, min(x1, x2))
        print('\np(x) = {:.4f} = {:.2f}%\n'.format(ans, ans * 100))






