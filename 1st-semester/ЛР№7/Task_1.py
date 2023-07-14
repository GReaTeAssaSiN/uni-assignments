import threading
import random
from string import ascii_letters
import time


# Функция генерации произвольных строк
def random_generation():
    while True:
        string = ''.join(random.choice(ascii_letters) for _ in range(random.randint(1, 100)))
        list_text.append(string)
        if len(list_text) > 100000:
            main_stream.daemon = True
            break


# Функция вывода текущего состояния списка на экран
def list_display():
    print('Текущее состояние списка построчно:')
    print()
    while True:
        print(list_text)
        print()
        if len(list_text) > 100000:
            display_stream.daemon = True
            break


# Функция сортировки списка в алфавитном и порядке и сортировка списка раз в 5 секунд с сохранением в файл
def list_sorted_writer():
    while True:
        time.sleep(5)
        list_text.sort()
        f = open('main_file.txt', 'w')
        for one_string in list_text:
            f.write(one_string + '\n')
        f.close()
        if len(list_text) > 100000:
            sort_writer_stream.daemon = True
            break


# Начальное состояние списка
list_text = []

# Задание главного потока и двух дочерних потоков
main_stream = threading.Thread(target=random_generation)
display_stream = threading.Thread(target=list_display)
sort_writer_stream = threading.Thread(target=list_sorted_writer)

# Начало работы заданных потоков
main_stream.start()
display_stream.start()
sort_writer_stream.start()
