# RuntimeError

dc = set()
while True:
    try:
        s = ''
        for i in input().lower():
            if i.isalpha():
                s += i
            elif len(s):
                dc.add(s)
                s = ''
    except EOFError:
        break
for w in sorted(dc):
    print(w)
