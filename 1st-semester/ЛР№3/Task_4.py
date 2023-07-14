def eratosphenes(n):
    a = [i for i in range(2, n+1)]
    for p in a:
        if p > 1:
            for j in range(2*p-2, len(a), p):
                a[j] = 0
    return a


print('Введите число n, до которого требуется сформировать список из целых натуральных чисел, т.е. от 1 до n:')
n = int(input())
if n >= 2:
    a, b = [i for i in range(1, n+1)], []
    print(a)
    for i in a:
        if i % 7 == 0:
            b.append(i)
    print('Пункт а). Все числа от 1 до n, кратные 7:', b)
    b = set(eratosphenes(n))
    b.remove(0)
    print('Пункт б). Все простые числа от 1 до n:', b)
else:
    print('Введите число n, не меньшее 2.')
