print('Введите строку, оканчивающуюся точкой:')
s = str(input())
print('Введите некоторый символ *:')
star = str(input())
k, space, count, maxs, mins = 0, 0, 0, 0, len(s)
for i in s:
    k += 1
    if i == '.':
        count += 1
    if (i == ' ') or (i == '.'):
        space += 1
        if (k-1) >= maxs:
            maxs = k - 1
        if (k-1) <= mins:
            mins = k - 1
        k = 0
if count > 0:
    print('Пункт a). Длина строки =', len(s))
    print('Пункт b). Количество слов в строке =', space)
    print('Длина самого короткого и длинного слова соответственно. Пункт c) =', mins, maxs)
    news = str()
    for i in s:
        if i != star:
            news = news + i*2
    print('Пункт d). Преобразованная строка =', news)
else:
    print('Вы ввели строку, не оканчивающуюся точкой.')
