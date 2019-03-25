k = int(input())

def f(n):
    if n == 1: return 0
    if n == 2: return 36
    if n % 2 == 0:
        return 36*10**(n-2) + 9*45*sum([10**(n-i) for i in range(4, n//2 + 3)])
    else:
        return f(n - 1) * 10

print(f(k))
