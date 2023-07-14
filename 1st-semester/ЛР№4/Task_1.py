import sys


# Функцмя для создания графа на основе введенного количества вершин и последовательности дуг
def read_graph():
    if 0 < n <= 10:
        graph = {}
        print('Введите последовательность дуг орграфа в виде "предшественник преемник" через запятую без отступов: ')
        d_matrix_in_str = str(input())
        or_graph = set(d_matrix_in_str)  # Для проверки истинности графа на орграф по определению
        or_graph.discard(' ')
        or_graph.discard(',')
        if len(or_graph) == n:
            for i in range(0, len(d_matrix_in_str), 4):
                a = int(d_matrix_in_str[i])
                b = int(d_matrix_in_str[i+2])
                if a == b:
                    print('У орграфа не может быть петли.')
                    sys.exit()
                else:
                    add_edge(graph, a, b)
            return graph
        else:
            print('Данный граф не является орграфом или количество вершин орграфа превышает введённое число n.')
            sys.exit()
    else:
        print('Число вершин орграфа не удовлетворяет условию.')


# Функция для вывода построенного орграфа
def add_edge(graph, a, b):
    if a not in graph:
        graph[a] = {}
    graph[a][b] = 'arc'


# Вывод орграфа
n = int(input('Введите число вершин орграфа n, где 0 < n <= 10: '))
graph = read_graph()
if 0 < n <= 10:
    print('Построенный орграф:', graph)
print()


# Функция поиска вершин, имеющих более двух преемников
def many_successors():
    print('a) Номера вершин орграфа, имеющие >2 преемников:')
    count = 0
    for key_ver in graph:
        if len(graph[key_ver]) > 2:
            print(key_ver)
            count += 1
    if count == 0:
        print('Нет таких вершин орграфа.')
    return print()


many_successors()


# Функция поиска вершин-преемников и всех вершин орграфа для упрощения следующих пунктов задачи
def successor_ver_find():
    successors_set = set()  # Множество вершин-преемников
    ver_set = set()  # Множество вершин орграфа
    for key_ver1 in graph:
        ver_set.add(key_ver1)
        for key_ver2 in graph[key_ver1]:
            successors_set.add(key_ver2)
            ver_set.add(key_ver2)
    return [successors_set, ver_set]


# Функция поиска вершин, не имеющих предшественников
def no_predecessor():
    print('б) Номера вершин орграфа, не имеющие предшественников:')
    successor_set = successor_ver_find()[0]
    ver_set = successor_ver_find()[1]
    ver_sp = ver_set.difference(successor_set)
    if len(ver_sp) != 0:
        for i in ver_sp:
            print(i)
    else:
        print('Нет таких вершин орграфа.')
    return print()


no_predecessor()


# Функция, ищущая для каждой вершины всех ее предшественников
def predecessor_find():
    print('в) Вершины и нормера всех их предшественников:')
    successors_set = successor_ver_find()[0]
    for elem in successors_set:
        count = 0
        for key_ver1 in graph:
            for key_ver2 in graph[key_ver1]:
                if elem == key_ver2:
                    if count == 0:
                        print(elem, '<--', end=' ')
                        count += 1
                    print(key_ver1, end=' ')
        print()
    return print()


predecessor_find()


# Функция, которая находит вершины, имеющие только одного преемника
def one_successor_find():
    print('г) Вершины в орграфе, имеющие только одного преемника:')
    count = 0
    for key_ver in graph:
        if len(graph[key_ver]) == 1:
            print(key_ver)
            count += 1
    if count == 0:
        print('Нет таких вершин орграфа.')
    return print()


one_successor_find()
