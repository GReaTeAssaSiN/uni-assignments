import random

print('Введите размеры матрицы A, т.е. числа n и m соответственно через пробел, где n - число строк, m - число столбцов:')
n, m = (int(i) for i in input().split())
a = [[' ']*m for i in range(n)]
for i in range(0, n):
    for j in range(0, m):
        a[i][j] = random.randint(-9, 9)
        print('%4d' % a[i][j], end=' ')
    print()
print('Преобразованная матрица A размеров m*n:')
for i in range(0, n):
    for j in range(0, m):
        if a[i][j] < 0:
            a[i][j] = abs(a[i][j])
        print('%4d' % a[i][j], end=' ')
    print()
