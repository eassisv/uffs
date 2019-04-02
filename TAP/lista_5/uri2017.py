x = input()
k = int(input())
w = idx = 1
diff = len(x)
while True:
    try:
        y = input()
        tmp = 0
        for i, j in zip(y, x):
            if i != j: tmp += 1

        if tmp < diff:
            diff = tmp
            idx = w

        w += 1
    except EOFError:
        break

if diff > k:
    print(-1)
else:
    print('{}\n{}'.format(idx, diff))

