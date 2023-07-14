import random

print('Введите количество элементов в списке:')
n = int(input())
if n >= 2:
    a = []
    b = []
    c = []
    for i in range(0, n):
        a.append(random.randint(-5, 1))
    print('Сгенерированный список:', a)
    m = max(a)
    for i in a:
        if i == 0:
            b.append(i)
    for i in range(0, n):
        if (a[i] != 0) and (a[i] != m):
            c.append(a[i])
        elif a[i] == m:
            c.append(a[i])
            for j in b:
                c.append(j)
            m += 1
    print('Преобразованный список:', c)
else:
    print('Список должен содержать как минимум 2 элемента.')
