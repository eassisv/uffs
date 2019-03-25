from math import ceil
MAX = int(2e6 + 10)

def setbit(i, v, bit):
    i += 1
    while i < MAX:
        bit[i] += v
        i += (i & -i)

def getbit(i, bit):
    i += 1
    t = 0
    while i > 0:
        t += bit[i]
        i -= (i & -i)
    return t

while True:
    bit_a = [0] * MAX
    bit_b = [0] * MAX
    try:
        n, e = map(int, input().split(' '))
    except:
        break
    if not n and not e: break
    As = list(map(int, input().split(' ')))
    Bs = list(map(int, input().split(' ')))
    for i, j in zip(As, Bs):
        setbit(i, 1, bit_a)
        setbit(j, 1, bit_b)
    a = b = v = 0
    while e:
        e -= 1
        l = input().split(' ')
        if l[0] == 'I' or l[0] == 'P':
            if l[1][0] == 'B':
                v = 0 if getbit(Bs[int(l[1][1]) - 1] - 1, bit_a) < ceil(n / 11) else 1
            else:
                v = 0 if n // 2 - getbit(As[int(l[1][1]) - 1], bit_b) < ceil(n / 11) else 1
        elif l[0] == 'M':
            setbit(*[As[int(l[1][1]) - 1], -1, bit_a] if l[1][0] == 'A' else [Bs[int(l[1][1]) - 1], -1, bit_b])
            if l[1][0] == 'A': As[int(l[1][1]) - 1] = int(l[2])
            else: Bs[int(l[1][1]) - 1] = int(l[2])
            setbit(*[As[int(l[1][1]) - 1], 1, bit_a] if l[1][0] == 'A' else [Bs[int(l[1][1]) - 1], 1, bit_b])
        elif l[0] == 'G':
            a += (v and l[1] == 'B')
            b += (v and l[1] == 'A')
    print('{} X {}'.format(a, b))
