print('Введите любую фразу от 10 символов:')
phrase = str(input())
if len(phrase) >= 10:
    print('Пункт а) =', phrase[0:4])
    print('Пункт б) =', phrase[(len(phrase)-4):])
    if len(phrase) % 2 == 1:
        print('Фраза имеет нечетное число символов. Пункт в) =', phrase[len(phrase)//2:len(phrase)//2+1])
    else:
        print('Фраза имеет четное число символов, поэтому найдены будут 2 символа по середине. Пункт в) =', phrase[len(phrase)//2-1:len(phrase)//2+1:1])
    print('Пункт г) =', phrase[2:8])
else:
    print('Вы ввели фразу длиной меньше 10 символов.')
