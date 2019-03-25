while True:
    h, u, d, f = [float(i) for i in input().split()]
    if h == 0.0: break
    ff = f * u * 0.01
    height = 0
    day = 1
    success = False
    while u >= 0.00000 and (height > 0.00000 or day == 1):
        # print('{:2d} {:5f} {:5f}'.format(day, height, u), end=' ')
        height = height + u
        # print('{:5f}'.format(height), end=' ')
        if height > h:
            print('success on day {}'.format(day))
            success = True
            break
        height = height - d
        u = 0.00000 if u <= 0.00000 else u - ff
        if height < 0.00000 or u < 0.00000:
            break
        # print('{:5f}'.format(height))
        day = day + 1
    if not success:
        print('failure on day {}'.format(day))


