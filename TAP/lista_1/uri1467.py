while True:
    try:
        a, b, c = [int(x) for x in input().split(' ')]
    except (EOFError, ValueError):
        break

    if a != b and a != c:
        print('A')
    elif b != a and b != c:
        print('B')
    elif c != a and c != b:
        print('C')
    else:
        print('*')
