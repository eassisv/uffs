# TLE

import heapq as pq ds = []
day = 1
while True:
    try:
        x, y = [int(x) for x in input().split(' ')]
        ds.append(tuple([x/y, y, day, x]))
        day += 1
    except (EOFError, ValueError):
        break

ans = 0
day = 1
q = []
pq.heappush(q, ds.pop(0))
while q != []:
    tp = pq.heappop(q)
    ans += (day - tp[2]) * tp[1]
    day += tp[3]
    while ds != []:
        if ds[0][2] > day: break
        pq.heappush(q, ds.pop(0))

print(ans)
