import random

print('Введите количество элементов в списке:')
n = int(input())
if n >= 2:
    a = []
    b = []
    stop = 0
    for i in range(0, n):
        a.append(random.randint(-10, 1))
    print('Сгенерированный список:', a)
    m = min(a)
    ind = a.index(m)
    print('Первый инимальный элемент списка и его индекс соответственно:', m, ind)
    for i in range(0, n):
        if i <= ind:
            b.append(a[i])
        elif (a[i] < 0) and (stop == 0):
            continue
        else:
            stop = 1
            b.append(a[i])
    print('Преобразованный список:', b)
else:
    print('Список должен содержать как минимум 2 элемента.')


