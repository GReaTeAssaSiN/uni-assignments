print('Введите |x|<∞ и n>=0 соответственно через пробел:')
x, n = (int(i) for i in input().split())
if n >= 0:
    s = 0
    for i in range(0, n+1, 1):
        factorial = 1
        for j in range(1, i+1, 1):
            factorial = factorial * j
        s = s + (((-1)**i)*(x**i))/factorial
    print('Значение искомой суммы ряда = ', s)
else:
    print('Вы ввели значение n, не удовлетворяющее условию задачию.')
