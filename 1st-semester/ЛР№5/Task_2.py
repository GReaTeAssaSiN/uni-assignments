# Чтение матрицы смежности графа из файла
f = open('Матрица_смежности.txt', 'r')
matrix_adjacency = [line.split() for line in f]

# Вывод матрицы смежности графа из файла и названия пунктов графа
print('Матрица смежности графа, моделирующего железнодорожную сеть:')
for i in range(len(matrix_adjacency)):
    for j in range(len(matrix_adjacency)):
        print("{:<7}".format(matrix_adjacency[i][j]), end='')
    print('\n')
mas_points = ['1. Казань', '2. Набережные Челны', '3. Нижнекамск', '4. Альметьевск', '5. Зеленодольск', '6. Бугульма',
              '7. Елабуга', '8. Лениногорск', '9. Чистополь', '10. Заинск', '11. Москва', '12. Санкт-Петербург',
              '13. Новосибирск', '14. Омск', '15. Ростов-на-Дону']
print('Пункты назначения карты:')
print('\n'.join(mas_points))

# Формирование матрицы смежности графа для алгоритма Дейкстры
inf = float('inf')
G = [[inf] * (len(matrix_adjacency)-1) for _ in range(len(matrix_adjacency)-1)]
for i in range(1, len(matrix_adjacency)):
    for j in range(1, len(matrix_adjacency)):
        if matrix_adjacency[i][j] != '0':
            G[i-1][j-1] = float(matrix_adjacency[i][j])

# Ввод необходимых пунктов от пользователя
print('Введите пункты, кратчайшее расстояние между которыми необходимо найти, через пробел:')
point_start, point_finish = input().split()
point_start = int(point_start) - 1
point_finish = int(point_finish) - 1


# Алгоритм Дейкстры
def dijkstra(G, s):
    n = len(G)

    Q = [(0, s)]

    d = [inf for _ in range(n)]
    d[s] = 0
    while len(Q) != 0:
        (cost, u) = Q.pop(0)

        for v in range(n):
            if d[v] > d[u] + G[u][v]:
                d[v] = round(d[u] + G[u][v], 1)
                Q.append((d[v], v))
    return d


# Получение пути
def getPath(k):
    global d
    n = len(G)

    path = [k]
    while k != point_start:
        for v in range(n):
            if d[v] == round(d[k] - G[k][v], 1):
                path.append(v)
                k = v
    return path[::-1]


# Вывод данных по запросу пользователя
d = dijkstra(G, point_start)
if point_start == point_finish:
    print('Вы уже находитессь в пункте назначения.')
elif d[point_finish] == inf:
    print('Вы не можете добраться из данного пункта до искомого в данный момент.')
else:
    print('Кратчайшее расстояние до искомого пункта равно:', d[point_finish])
    print('Путь движения:', end=' ')
    path = getPath(point_finish)
    for i in range(len(path)):
        if i != len(path) - 1:
            print(path[i]+1, '->', end=' ')
        else:
            print(path[i]+1, end='.')
