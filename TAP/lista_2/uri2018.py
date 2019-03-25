qm = {}
def updt(c, tp):
    if c not in qm:
        qm[c] = tp
    else:
        tmp = tuple()
        for i, j in zip(qm[c], tp):
            tmp += (i + j,)
        qm[c] = tmp


while True:
    try:
        input()
        updt(input(), (1, 0, 0))
        updt(input(), (0, 1, 0))
        updt(input(), (0, 0, 1))
    except EOFError:
        break

oqm = {}
for k, v in sorted(qm.items()):
    if v not in oqm:
        oqm[v] = [k]
    else:
        oqm[v].append(k)
print('Quadro de Medalhas')
for k, v in sorted(oqm.items())[::-1]:
    for i in v:
        print('{} {} {} {}'.format(i, k[0], k[1], k[2]))
