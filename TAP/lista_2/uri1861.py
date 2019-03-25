ms = {}
ds = set()
while True:
    try:
        n, m = input().split(' ')
        ds.add(m)
        if n in ms:
            ms[n] += 1
        else:
            ms[n] = 1
    except (ValueError, EOFError):
        break

for i in ds:
    if i in ms: del ms[i]
print('HALL OF MURDERERS')
for i in sorted(ms.keys()): print('{} {}'.format(i, ms[i]))

