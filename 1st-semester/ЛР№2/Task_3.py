print('Введите последовательно через запятую 6 целых десятичных чисел:')
list = str(input())
a = []
k = str()
if len(list) >= 11:
    for i in list:
        if i != ',':
            k += i
        else:
            a.append(k)
            k = str()
    k = str()
    for i in list[::-1]:
        if i != ',':
            k += i
        else:
            k = k[::-1]
            a.append(k)
            k = str()
            break
    if len(a) == 6:
        print('Пункт а) =', a[3])
        print('Пункт б) =', a[5::-1])
        s = 0
        for i in range (0, 6, 1):
            s = s + int(a[i])
        print('Сумма и среднее арифметическое соответственно. Пункт в) =', s, ' ', s/6)
    else:
        print('Введённый список не удовлетворяет условиям задачи.')
else:
    print('Введённый список не удовлетворяет условиям задачи.')
