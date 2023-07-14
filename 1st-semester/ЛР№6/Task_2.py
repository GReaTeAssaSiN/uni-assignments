from tkinter import *
import random

# Создание окна
root = Tk()
root.title("Game Snake")

# Ширина окна
root_width = 800
# Высота окна
root_height = 600
# Размер сегмента змейки
snake_size = 20
# Состояние игры
game_in = True


# Создание змейки в начале игры
def create_snake():
    # Набор сегментов
    snake_segments = [Segment(snake_size, snake_size),
                      Segment(snake_size * 2, snake_size),
                      Segment(snake_size * 3, snake_size)]
    return Snake(snake_segments)


# Создание сегментов змейки при выполнении действия
class Segment(object):
    def __init__(self, x, y):
        self.instance = c.create_rectangle(x, y, x + snake_size, y + snake_size, fill="grey")


# Создание яблок на холсте в случайной позиции
def create_apple():
    global block
    posx = snake_size * (random.randint(1, (root_width - snake_size) // snake_size))
    posy = snake_size * (random.randint(1, (root_height - snake_size) // snake_size))

    # Формирование яблока
    block = c.create_oval(posx, posy, posx + snake_size, posy + snake_size, fill="red")


# Операции над змейкой
class Snake(object):
    # Обновление сегментов змейки
    def __init__(self, snake_segments):
        self.segments = snake_segments

        # Доступные направления движения змейки
        self.movement = {"Down": (0, 1), "Up": (0, -1), "Left": (-1, 0), "Right": (1, 0)}
        # Начальный вектор движения змейки
        self.vector = self.movement["Right"]

    # Движение змейки в заданном направлении
    def move(self):
        for index in range(len(self.segments) - 1):
            segment = self.segments[index].instance
            # Координаты сегмента, стоящего после полученного сегмента
            x1, y1, x2, y2 = c.coords(self.segments[index + 1].instance)
            # Задание сегменту координат сегмента, стоящего после него
            c.coords(segment, x1, y1, x2, y2)

        # Координаты сегмента перед "головой" змейки
        x1, y1, x2, y2 = c.coords(self.segments[-2].instance)

        # Перемещение "головы" змейки в направлении указанного движения
        c.coords(self.segments[-1].instance,
                 x1 + self.vector[0] * snake_size, y1 + self.vector[1] * snake_size,
                 x2 + self.vector[0] * snake_size, y2 + self.vector[1] * snake_size)

    # Добавление сегмента змейке
    def add_segment(self):
        # Последний сегмент змейки
        last_snake_segment = c.coords(self.segments[0].instance)
        # Коордтнаты следующего сегмента змейки
        x = last_snake_segment[2] - snake_size
        y = last_snake_segment[3] - snake_size
        # Добавление змейке сегмента в заданных координатах
        self.segments.insert(0, Segment(x, y))

    # Изменение направления движения змейки
    def change_direction(self, event):
        # event передает символ нажатой клавиши
        # Если она присутствует в возможных клавишах, изменяет направление змейки
        if event.keysym in self.movement:
            self.vector = self.movement[event.keysym]

    # Сброс сегментов змейки в случае проигрыша
    def reset_snake(self):
        for segment in self.segments:
            c.delete(segment.instance)


# Тело игры
def main():
    global game_in
    if game_in:
        # Двигаем змейку
        s.move()
        # Определеяем координаты "головы" змейки
        head_snake_coords = c.coords(s.segments[-1].instance)
        x1, y1, x2, y2 = head_snake_coords
        # Учет столкновения с границами экрана
        if x1 < 0 or x2 > root_width or y1 < 0 or y2 > root_height:
            game_in = False
        # Поедание "змейкой" яблок
        elif head_snake_coords == c.coords(block):
            s.add_segment()
            c.delete(block)
            create_apple()
        # Самоедство
        else:
            # Проверяем совпадение координат головы с координатами какого-либо сегмента змеи
            for index in range(len(s.segments) - 1):
                if c.coords(s.segments[index].instance) == head_snake_coords:
                    game_in = False
        root.after(100, main)
    # Проигрыш
    else:
        set_state(restart_text, 'normal')
        set_state(game_over_text, 'normal')


# Появление невидимомого текста при поражении
def set_state(item, state):
    c.itemconfigure(item, state=state)


# Пересоздание игры после нажатия на "clicked here to restart"
def clicked(event):
    global game_in
    s.reset_snake()
    game_in = True
    c.delete(block)
    c.itemconfigure(restart_text, state='hidden')
    c.itemconfigure(game_over_text, state='hidden')
    start_game()


# Начало игры после поражения
def start_game():
    global s
    create_apple()
    s = create_snake()
    # Реакция на нажатие клавиш
    c.bind("<KeyPress>", s.change_direction)
    main()


# Создание холста окна
c = Canvas(root, width=root_width, height=root_height, bg="#003300")
c.grid()
# Реагирование холста на нажатие клавиш
c.focus_set()

# Текст холста при проигрыше и начале игры заново
game_over_text = c.create_text(root_width / 2, root_height / 2, text="GAME OVER!",
                               font='Arial 20', fill='red',
                               state='hidden')
restart_text = c.create_text(root_width / 2, root_height - root_height / 3,
                             font='Arial 30',
                             fill='black',
                             text="Click here to restart",
                             state='hidden')

# Начало игры заново
c.tag_bind(restart_text, "<Button-1>", clicked)
# Начало игры
start_game()

root.mainloop()
