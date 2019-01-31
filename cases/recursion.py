def f(x):
    if x > 10:
        return
    else:
        f(x + 1)
    print x


f(1)


def sum_n(n):
    if n== 0:
        return 0
    else:
        return n + sum_n(n-1)

print sum_n(5) 
