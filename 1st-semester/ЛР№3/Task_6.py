import random

print('Введённый массив T размерности 3*5*7:')
T = [[[[' '] for i in range(0, 7)] for j in range(0, 5)] for k in range(0, 3)]
for k in range(0, 3):
    for j in range(0, 5):
        for i in range(0, 7):
            T[k][j][i] = random.randint(-1000, 1000)
            print('%4d' % T[k][j][i], end=' ')
        print()
    print()
ind = str()
m = T[0][0][0]
for k in range(0, 3):
    for j in range(0, 5):
        for i in range(0, 7):
            if T[k][j][i] > m:
                m = T[k][j][i]
                ind = '['+str(k)+']'+'['+str(j)+']'+'['+str(i)+']'
print('Максимальный эллемент массива T:', m, 'с индексами', ind)
