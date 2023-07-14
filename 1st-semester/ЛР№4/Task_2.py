def euclid(m, n):
    if (m == 0) or (n == 0):
        return n + m
    elif m < n:
        return euclid(n, m)
    else:
        return euclid(m - n, n)


print('Введите целые положительные числа n и m соответственно через пробел, НОД которых необходимо найти:')
n, m = input().split()
n = int(n)
m = int(m)
if (n >= 0) and (m >= 0):
    if (m ==0) and (n == 0):
        print('Нельзя определить НОД данных чисел, т.к. на 0 делить нельзя, а бесконечность не определена.')
    else:
        print('НОД данных чисел равен =', euclid(m, n))
else:
    print('Введите положительные значения n и m.')
